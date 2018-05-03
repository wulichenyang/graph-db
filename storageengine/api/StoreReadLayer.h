#pragma once
#include "../../kernel/impl/store/RelationshipStore.h"
#include "../../kernel/impl/store/RecordStore.h"
#include "../../kernel/impl/core/PropertyKeyTokenHolder.h"
#include "../../kernel/impl/core/LabelTokenHolder.h"
#include "../../kernel/impl/core/RelationshipTypeTokenHolder.h"
#include "../../kernel/impl/store/NodeStore.h"
#include "../../kernel/impl/store/NeoStores.h"
#include "../../storageengine/api/StorageStatement.h"

class StoreReadLayer
{
public:
	StoreReadLayer();
	~StoreReadLayer();
	StoreReadLayer(PropertyKeyTokenHolder *propertyKeyTokenHolder, LabelTokenHolder *labelTokenHolder,
		RelationshipTypeTokenHolder *relationshipTokenHolder, NeoStores *neoStores);
	StorageStatement *newStatement();


private:
	PropertyKeyTokenHolder *propertyKeyTokenHolder;
	// ReplicatedLabelTokenHolder extends ReplicatedTokenHolder<Token> implements LabelTokenHolder
	LabelTokenHolder *labelTokenHolder;
	// ReplicatedRelationshipTypeTokenHolder extends
	//   ReplicatedTokenHolder<RelationshipTypeToken> implements RelationshipTypeTokenHolder
	RelationshipTypeTokenHolder *relationshipTokenHolder;
	NodeStore *nodeStore;
	RelationshipStore *relationshipStore;
};

