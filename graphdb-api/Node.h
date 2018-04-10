#pragma once
#include "Entity.h"
#include "Relationship.h"
#include "RelationshipType.h"
#include <vector>

using namespace std;

class Node: public Entity
{
public:
	Node();
	virtual ~Node();
	virtual long getId() const = 0;
	virtual void remove() = 0;
	virtual vector<Relationship>::iterator getRelationships() const = 0;
	virtual vector<Relationship>::iterator getRelationships(RelationshipType types) const = 0;
	Relationship createRelationshipTo(Node *otherNode, RelationshipType type) = 0;
};

