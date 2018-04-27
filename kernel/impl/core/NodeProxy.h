#pragma once
#include "../../../graphdb-api/Entity.h"
#include "../../../graphdb-api/Node.h"
#include "../../../graphdb-api/RelationshipType.h"
#include "../core/EmbeddedProxySPI.h"
#include "RelationshipProxy.h"
#include <vector>

using namespace std;

class NodeProxy: public Node
{
public:
	NodeProxy();
	NodeProxy(EmbeddedProxySPI *spi, const long &nodeId);
	~NodeProxy();
	long getId() const override;
	void remove() override;
	vector<Relationship> getRelationships() const;
	vector<Relationship> getRelationships(const RelationshipType &type) const;
	RelationshipProxy createRelationshipTo(const NodeProxy &otherNode, const RelationshipType &type);
	string toString() const;
private:
	EmbeddedProxySPI *spi;
	long nodeId;
};

