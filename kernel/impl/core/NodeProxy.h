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
	NodeProxy(EmbeddedProxySPI *spi, long nodeId);
	~NodeProxy();
	long getId() const override;
	void remove() override;
	vector<Relationship*>::iterator getRelationships() const override;
	vector<Relationship*>::iterator getRelationships(RelationshipType type) const override;
	Relationship *createRelationshipTo(Node *otherNode, RelationshipType type) override;
	string toString() const;
private:
	EmbeddedProxySPI *spi;
	long nodeId;
};

