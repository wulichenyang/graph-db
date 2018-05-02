#pragma once
#include "../../kernel/impl/store/NeoStores.h"
#include "../../kernel/impl/store/NodeStore.h"
#include "../../kernel/impl/core/LabelTokenHolder.h"
#include "../../kernel/impl/core/RelationshipTypeTokenHolder.h"
#include "../../kernel/impl/core/PropertyKeyTokenHolder.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "../../io/fs/FileChannel.h"
#include "../../kernel/impl/store/id/IdGeneratorFactory.h"
#include "../../storageengine/api/StoreReadLayer.h"
#include "../../kernel/impl/store/StoreFactory.h"

class StorageEngine
{
public:
	StorageEngine(
	char *storeDir,
	PropertyKeyTokenHolder *propertyKeyTokenHolder,
	LabelTokenHolder *labelTokens,
	RelationshipTypeTokenHolder *relationshipTypeTokens,
	IdGeneratorFactory *idGeneratorFactory,
	FileChannel *file);

	StorageEngine();
	~StorageEngine();

private:
	StoreReadLayer *storeLayer;
	NeoStores *neoStores;
	PropertyKeyTokenHolder *propertyKeyTokenHolder;
	RelationshipTypeTokenHolder *relationshipTypeTokenHolder;
	LabelTokenHolder *labelTokenHolder;
	int recordIdBatchSize;
};

