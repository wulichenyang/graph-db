#include "NodeProxy.h"



NodeProxy::NodeProxy()
{
}


NodeProxy::NodeProxy(EmbeddedProxySPI * spi, long nodeId)
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

vector<Relationship>::iterator NodeProxy::getRelationships() const
{
	return vector<Relationship>::iterator();
}

vector<Relationship>::iterator NodeProxy::getRelationships(RelationshipType types) const
{
	return vector<Relationship>::iterator();
}

Relationship *NodeProxy::createRelationshipTo(Node * otherNode, RelationshipType type)
{
	return Relationship();
}
