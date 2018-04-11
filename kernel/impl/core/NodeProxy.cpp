#include "NodeProxy.h"



NodeProxy::NodeProxy(EmbeddedProxySPI * spi, const long & nodeId)
{
}

NodeProxy::~NodeProxy()
{
}

long NodeProxy::getId() const
{
	return 0;
}

void NodeProxy::remove()
{
}

vector<Relationship*>::iterator NodeProxy::getRelationships() const
{
	return vector<Relationship*>::iterator();
}

vector<Relationship*>::iterator NodeProxy::getRelationships(RelationshipType type) const
{
	return vector<Relationship*>::iterator();
}

Relationship * NodeProxy::createRelationshipTo(Node * otherNode, RelationshipType type)
{
	return nullptr;
}

string NodeProxy::toString() const
{
	return string();
}

