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

vector<RelationshipProxy> NodeProxy::getRelationships() const
{
	return vector<RelationshipProxy>();
}

vector<RelationshipProxy> NodeProxy::getRelationships(const RelationshipType & type) const
{
	return vector<RelationshipProxy>();
}

RelationshipProxy NodeProxy::createRelationshipTo(const NodeProxy & otherNode, const RelationshipType & type)
{
	return RelationshipProxy();
}

string NodeProxy::toString()
{
	return string();
}

