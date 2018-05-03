#include "StorageEngine.h"



StorageEngine::StorageEngine(char * storeDir, PropertyKeyTokenHolder *propertyKeyTokenHolder, LabelTokenHolder *labelTokens, RelationshipTypeTokenHolder *relationshipTypeTokens, IdGeneratorFactory *idGeneratorFactory, FileChannel *file)
{
	this->propertyKeyTokenHolder = propertyKeyTokenHolder;
	this->relationshipTypeTokenHolder = relationshipTypeTokens;
	this->labelTokenHolder = labelTokens;

	StoreFactory *factory = new StoreFactory(storeDir, idGeneratorFactory, file);
	neoStores = factory->openAllNeoStores(true);

	try
	{
		cacheAccess = new CacheAccess(propertyKeyTokenHolder, relationshipTypeTokens, labelTokens);
		storeLayer = new StoreReadLayer(
			propertyKeyTokenHolder, labelTokens, relationshipTypeTokens,
			neoStores);
		recordIdBatchSize = 20;
	}
	catch (const std::exception& e)
	{
		neoStores->close();
		throw e;
	}
}

StorageEngine::StorageEngine()
{
}


StorageEngine::~StorageEngine()
{
}

StoreReadLayer * StorageEngine::storeReadLayer()
{
	return this->storeLayer;
}
