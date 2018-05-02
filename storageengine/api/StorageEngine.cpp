#include "StorageEngine.h"



StorageEngine::StorageEngine(char * storeDir, PropertyKeyTokenHolder *propertyKeyTokenHolder, LabelTokenHolder *labelTokens, RelationshipTypeTokenHolder *relationshipTypeTokens, IdGeneratorFactory *idGeneratorFactory, FileChannel *file)
{
	this->propertyKeyTokenHolder = propertyKeyTokenHolder;
	this->relationshipTypeTokenHolder = relationshipTypeTokens;
	this->labelTokenHolder = labelTokens;

	StoreFactory *factory = new StoreFactory(storeDir, idGeneratorFactory, file);
	neoStores = factory->openAllNeoStores(true);
}

StorageEngine::StorageEngine()
{
}


StorageEngine::~StorageEngine()
{
}
