#include "NodeProxy.h"


NodeProxy::NodeProxy() {

}

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

vector<Relationship> NodeProxy::getRelationships(const RelationshipType & type) const
{
	return vector<Relationship>();
}

RelationshipProxy NodeProxy::createRelationshipTo(const NodeProxy & otherNode, const RelationshipType & type)
{
	return RelationshipProxy();
}

string NodeProxy::toString() const
{
	return string();
}

