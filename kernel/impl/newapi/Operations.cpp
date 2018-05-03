#include "Operations.h"



Operations::Operations()
{
}

Operations::Operations(AllStoreHolder * allStoreHolder, StorageStatement * statement, KernelTransaction * ktx, KernelToken * token)
{
	this->allStoreHolder = allStoreHolder;
	this->statement = statement;
	this->ktx = ktx;
	this->token = token;
}


Operations::~Operations()
{
}

long Operations::nodeCreate()
{
	ktx->assertOpen();
	long nodeId = statement->reserveNode();
	ktx->txState()->nodeDoCreate(nodeId);
	return nodeId;
}
