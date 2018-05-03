#include "StorageStatement.h"



StorageStatement::StorageStatement()
{
}


StorageStatement::~StorageStatement()
{
}

StorageStatement::StorageStatement(NeoStores * neoStores, RecordStorageCommandCreationContext * commandCreationContext)
{
	this->neoStores = neoStores;
	this->commandCreationContext = commandCreationContext;

	this->nodeStore = neoStores->getNodeStore();
	this->relationshipStore = neoStores->getRelationshipStore();
}

long StorageStatement::reserveNode()
{
	return commandCreationContext->nextId(StoreType::NODE);
}

long StorageStatement::reserveRelationship()
{
	return commandCreationContext->nextId(StoreType::RELATIONSHIP);
}
