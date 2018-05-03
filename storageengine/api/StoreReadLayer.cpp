#include "StoreReadLayer.h"



StoreReadLayer::StoreReadLayer()
{
}


StoreReadLayer::~StoreReadLayer()
{
}

StoreReadLayer::StoreReadLayer(PropertyKeyTokenHolder * propertyKeyTokenHolder, LabelTokenHolder * labelTokenHolder, RelationshipTypeTokenHolder * relationshipTokenHolder, NeoStores * neoStores)
{
	this->relationshipTokenHolder = relationshipTokenHolder;
	this->propertyKeyTokenHolder = propertyKeyTokenHolder;
	this->labelTokenHolder = labelTokenHolder;
	this->nodeStore = neoStores->getNodeStore();
	this->relationshipStore = neoStores->getRelationshipStore();
}

StorageStatement *StoreReadLayer::newStatement()
{
	return new StorageStatement();
}
