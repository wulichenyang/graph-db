#include "RelationshipState.h"



RelationshipState::RelationshipState()
{
}

RelationshipState::RelationshipState(long id)
	:PropertyContainerState(id)
{
}


RelationshipState::~RelationshipState()
{
}

void RelationshipState::setMetaData(long startNode, long endNode, int type)
{
	this->startNode = startNode;
	this->endNode = endNode;
	this->type = type;
}
