#pragma once
#include "../../../graphdb-api/Relationship.h"
#include "../../../graphdb-api/Node.h"
#include "../../../graphdb-api/RelationshipType.h"
#include "../core/EmbeddedProxySPI.h"
#include <vector>

#define NO_ID -1;

using namespace std;

class RelationshipProxy: public Relationship
{
public:
	RelationshipProxy();
	~RelationshipProxy();
	long getId() const override;
	int typeId() const;
	long sourceId() const;
	long targetId() const;
	void remove() override;
	Node *getStartNode() const override;
	Node *getEndNode() const override;
	RelationshipType getType() const override;
	bool isType(RelationshipType type) const override;
	long getStartNodeId() const override;
	long getEndNodeId() const override;
	long getOtherNodeId(long id) const override;

private:
	EmbeddedProxySPI actions;
	long id = NO_ID;
	long startNode = NO_ID;
	long endNode = NO_ID;
	int type;
};

