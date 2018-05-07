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
	// ��ʼ������Token Holder������Store���������Ѿ��洢������
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
		// StorageEngine��txState.accept()
		// ����TransactionRecordState.extractCommands
		storageEngine->createCommands(
			// Collection<xxCommand>
			extractedCommands,
			// TxState
			txState,
			// StoreStatement
			storageStatement,
			// SimpleStatementLocks
			commitLocks);

		if (!extractedCommands->isEmpty())
		{
			// Finish up the whole transaction representation

			// Commit the transaction
			success = true;

			// �� extractedCommands ��װ�� TransactionToApply batch ��������
			// �ں� transactionId �� nextTxToApply
			// batch -> new TransactionToApply(PhysicalTransactionRepresentation)
			for (size_t i = 0; i < extractedCommands->size(); i++)
			{
				extractedCommands[i].handle(applier);
			}
			TransactionToApply batch = new TransactionToApply(transactionRepresentation);

			// TransactionRepresentationCommitProcess.commit(TransactionToApply, ...)
			// ��TransactionToApply���physicaltx���commands�ֱ�ʵ��xxCommit���ܣ���ʱ��
			txId = transactionId = commitProcess.commit(batch);
			commitTime = timeCommitted;
		}
	}
	success = true;
	return 0;
}
