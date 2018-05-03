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
