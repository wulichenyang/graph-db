#pragma once
#include "../../storageengine/api/StorageEngine.h"
#include "../../storageengine/api/StoreReadLayer.h"
#include "txstate/TxState.h"
#include "../../kernel/api/KernelStatement.h"
#include "../../storageengine/api/StorageStatement.h"
#include "../impl/newapi/Operations.h"
#include "../impl/transaction/command/Command.h"
#include "../impl/newapi/KernelToken.h"
#include "../impl/newapi/AllStoreHolder.h"
#include "../impl/newapi/NodeCursor.h"
#include "../../kernel/internal/TokenWrite.h"
#include "../../kernel/internal/TokenRead.h"

class KernelTransaction
{
public:
	KernelTransaction();
	KernelTransaction(StorageEngine *storageEngine,
		KernelToken *token);
	~KernelTransaction();
	KernelTransaction *initialize();
	void success();
	bool isSuccess();
	void failure();
	bool isOpen();
	KernelStatement *acquireStatement();
	void upgradeToDataWrites();
	TxState *getTxState();
	bool hasTxStateWithChanges();
	void assertOpen();
	bool hasChanges();
	bool hasExplicitIndexChanges();
	bool hasDataChanges();
	bool hasDataChanges();
	TokenWrite *tokenWrite();
	TokenRead *tokenRead();
	Operations *dataWrite();

private:
	const static long NOT_COMMITTED_TRANSACTION_ID = -1;
	const static long NOT_COMMITTED_TRANSACTION_COMMIT_TIME = -1;

	bool closing;
	bool closed;
	bool failure;
	bool success;

	StorageEngine *storageEngine;
	StoreReadLayer *storeLayer;
	TxState *txState;
	// Statement(simple read/write operations)
	KernelStatement *currentStatement;
	StorageStatement *storageStatement;
	// Write operations
	Operations *operations;
	NeoStoreTransactionApplier applier;


	void markAsClosed(const long &txId);
	void closeCurrentStatementIfAny();
	void assertTransactionNotClosing();
	void assertTransactionOpen();
	bool hasChanges();
	bool hasExplicitIndexChanges();
	bool hasDataChanges();
	long closeTransaction();
	bool isClosing();

	long commit();
	void rollback();

	void afterCommit(const long &txId);
	void afterRollback();
	void release();
	bool canBeTerminated();
	bool isTerminated();
	void dispose();
	NodeCursor *nodeCursor();

};

