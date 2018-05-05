#include "KernelTransaction.h"


KernelTransaction::KernelTransaction()
{
}

KernelTransaction::KernelTransaction(StorageEngine * storageEngine, KernelToken * token)
{
	this->storeLayer = storageEngine->storeReadLayer();
	this->storageEngine = storageEngine;
	this->storageStatement = storeLayer->newStatement();
	//this->currentStatement = new KernelStatement(this, storageStatement, statementOperations);
	// 初始化各种Token Holder，各种Store，读磁盘已经存储的数据
	AllStoreHolder *allStoreHolder =
		new AllStoreHolder(storageEngine, storageStatement, this);
	this->operations =
		new Operations(
			allStoreHolder,
			storageStatement,
			this, token);
}


KernelTransaction::~KernelTransaction()
{
}

Operations * KernelTransaction::dataWrite()
{
	return this->operations;
}

TxState * KernelTransaction::getTxState()
{
	return this->txState;
}

bool KernelTransaction::hasTxStateWithChanges()
{
	return txState->ifHasChanges();
}

long KernelTransaction::commit()
{
	bool success = false;
	// Convert changes into commands and commit
	if (hasChanges())
	{
		// grab all optimistic locks now, locks can't be deferred any further

		//statementLocks.prepareForCommit(currentStatement.lockTracer());

		// use pessimistic locks for the rest of the commit process, locks can't be deferred any further

		//Locks.Client commitLocks = statementLocks.pessimistic();

		// Gather up commands from the various sources

		// in Command.java
		// NodeCommand -> BaseCommand -> Command -> StorageCommand
		// RelationshipCommand -> BaseCommand -> Command -> StorageCommand
		// ...

		vector<Command> *extractedCommands = new vector<Command>();
		// RecordStorageEngine.createCommands()
		storageEngine.createCommands(
			// Collection<xxCommand>
			extractedCommands,
			// TxState
			txState,
			// StoreStatement
			storageStatement,
			// SimpleStatementLocks
			commitLocks,
			lastTransactionIdWhenStarted);
		if (hasExplicitIndexChanges())
		{
			explicitIndexTransactionState.extractCommands(extractedCommands);
		}

		/* Here's the deal: we track a quick-to-access hasChanges in transaction state which is true
		* if there are any changes imposed by this transaction. Some changes made inside a transaction undo
		* previously made changes in that same transaction, and so at some point a transaction may have
		* changes and at another point, after more changes seemingly,
		* the transaction may not have any changes.
		* However, to track that "undoing" of the changes is a bit tedious, intrusive and hard to maintain
		* and get right.... So to really make sure the transaction has changes we re-check by looking if we
		* have produced any commands to add to the logical log.
		*/
		if (!extractedCommands.isEmpty())
		{
			// Finish up the whole transaction representation

			// 添加一些用户id和时间等信息，忽略暂时
			PhysicalTransactionRepresentation transactionRepresentation =
				new PhysicalTransactionRepresentation(extractedCommands);
			TransactionHeaderInformation headerInformation = headerInformationFactory.create();
			long timeCommitted = clock.millis();
			transactionRepresentation.setHeader(headerInformation.getAdditionalHeader(),
				headerInformation.getMasterId(),
				headerInformation.getAuthorId(),
				startTimeMillis, lastTransactionIdWhenStarted, timeCommitted,
				commitLocks.getLockSessionId());

			// Commit the transaction
			success = true;
			// commands封装在PhysicalTransactionRepresentation，内含开始时间和提交时间，masterId和authorId
			// extractedCommands -> PhysicalTransactionRepresentation(extractedCommands)

			// 将 PhysicalTransactionRepresentation 封装在 TransactionToApply batch 的链表里
			// 内含 transactionId 和 nextTxToApply
			// batch -> new TransactionToApply(PhysicalTransactionRepresentation)
			TransactionToApply batch = new TransactionToApply(transactionRepresentation);

			// TransactionRepresentationCommitProcess.commit(TransactionToApply, ...)
			// 把TransactionToApply里的physicaltx里的commands分别实现xxCommit功能（暂时）
			txId = transactionId = commitProcess.commit(batch, commitEvent, INTERNAL);
			commitTime = timeCommitted;
		}
	}
	success = true;
	return 0;
}
