#pragma once
#include "Entity.h"
#include "Relationship.h"
#include "RelationshipType.h"
#include <vector>

using namespace std;

class Node: public Entity
{
public:
	virtual long getId() const override = 0;
	virtual void remove() = 0;
	virtual vector<Relationship*>::iterator getRelationships() const = 0;
	virtual vector<Relationship*>::iterator getRelationships(RelationshipType type) const = 0;
	virtual Relationship* createRelationshipTo(Node *otherNode, RelationshipType type) = 0;
};