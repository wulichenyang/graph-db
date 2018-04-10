#include "RelationshipProxy.h"



RelationshipProxy::RelationshipProxy()
{
}


RelationshipProxy::~RelationshipProxy()
{
}

long RelationshipProxy::getId() const
{
	return 0;
}

int RelationshipProxy::typeId() const
{
	return 0;
}

long RelationshipProxy::sourceId() const
{
	return 0;
}

long RelationshipProxy::targetId() const
{
	return 0;
}

void RelationshipProxy::remove()
{
}

Node * RelationshipProxy::getStartNode() const
{
	return nullptr;
}

Node * RelationshipProxy::getEndNode() const
{
	return nullptr;
}

RelationshipType RelationshipProxy::getType() const
{
	return RelationshipType(string());
}

bool RelationshipProxy::isType(RelationshipType type) const
{
	return false;
}

long RelationshipProxy::getStartNodeId() const
{
	return 0;
}

long RelationshipProxy::getEndNodeId() const
{
	return 0;
}

long RelationshipProxy::getOtherNodeId(long id) const
{
	return 0;
}
