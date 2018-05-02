#pragma once
#include "NodeStore.h"
#include "RelationshipStore.h"

class NeoStores
{
public:
	NeoStores();
	~NeoStores();
	void close();
	NodeStore *getNodeStore();
	RelationshipStore *getRelationshipStore();
};

