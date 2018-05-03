#pragma once
#include "../../kernel/impl/store/PropertyStore.h"
#include "../../kernel/impl/storageengine/impl/recordstorage/RecordStorageCommandCreationContext.h"
#include "../../kernel/impl/store/NeoStores.h"

class StorageStatement
{
public:
	StorageStatement();
	~StorageStatement();

	StorageStatement(NeoStores *neoStores, RecordStorageCommandCreationContext *commandCreationContext);

	long reserveNode();
	long reserveRelationship();


private:
	NeoStores *neoStores;
	NodeStore *nodeStore;
	RelationshipStore *relationshipStore;
	PropertyStore *propertyStore;
	RecordStorageCommandCreationContext *commandCreationContext;

	bool acquired;
	bool closed;
};

