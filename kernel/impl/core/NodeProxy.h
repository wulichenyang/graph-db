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
	NodeProxy();
	NodeProxy(EmbeddedProxySPI *spi, long nodeId);
	virtual ~NodeProxy();
	long getId() const;
	void remove();
	vector<Relationship>::iterator getRelationships() const;
	vector<Relationship>::iterator getRelationships(RelationshipType types) const;
	Relationship *createRelationshipTo(Node *otherNode, RelationshipType type);
	string toString() const;
private:
	EmbeddedProxySPI *spi;
	long nodeId;
};

