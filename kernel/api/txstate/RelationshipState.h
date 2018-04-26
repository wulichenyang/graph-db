#pragma once
#include "TxState.h"
#include "PropertyContainerState.h"

class RelationshipState: public PropertyContainerState
{
public:
	RelationshipState();
	RelationshipState(long id);
	~RelationshipState();
	void setMetaData(long startNode, long endNode, int type);

private:
	long startNode = -1;
	long endNode = -1;
	int type = -1;
};

