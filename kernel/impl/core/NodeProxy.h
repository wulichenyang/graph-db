#pragma once
#include "../../../graphdb-api/Entity.h"
#include "../../../graphdb-api/Node.h"
#include "../../../graphdb-api/RelationshipType.h"
#include "../core/EmbeddedProxySPI.h"
#include <vector>

using namespace std;

class NodeProxy: public Node
{
public:
	NodeProxy(EmbeddedProxySPI *spi, const long &nodeId);
	~NodeProxy();
	long getId() const override;
	void remove() override;
	vector<Relationship*>::iterator getRelationships() const;
	vector<Relationship*>::iterator getRelationships(RelationshipType type) const;
	Relationship *createRelationshipTo(Node *otherNode, RelationshipType type);
	string toString() const;
private:
	EmbeddedProxySPI *spi;
	long nodeId;
};

