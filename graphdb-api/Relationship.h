#pragma once
#include "Entity.h"
#include "Node.h"
#include "RelationshipType.h"

class Relationship: public Entity 
{
public:
	Relationship();
	virtual ~Relationship();
	virtual long getId() const = 0;
	virtual void remove() = 0;
	virtual Node *getStartNode() const = 0;
	virtual Node *getEndNode() const = 0;
	virtual RelationshipType getType() const = 0;
	virtual bool isType(RelationshipType type) const = 0;
	virtual long getStartNodeId() const = 0;
	virtual long getEndNodeId() const = 0;
	virtual long getOtherNodeId(long id) const = 0;
};

