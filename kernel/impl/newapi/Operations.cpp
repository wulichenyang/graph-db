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
	// statement ��� context ����ĳЩ״̬
	long nodeId = statement->reserveNode();
	ktx->txState()->nodeDoCreate(nodeId);
	return nodeId;
}

bool Operations::nodeDelete(long node)
{
	ktx->assertOpen();
	if (ktx->hasTxStateWithChanges())
	{
		ktx->txState()->nodeDoDelete(node);
		return true;
	}
	if (ktx->txState()->nodeIsDeletedInThisTx(node))
	{
		// already deleted
		return false;
	}
	return false;
}
