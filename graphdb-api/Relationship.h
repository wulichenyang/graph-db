#pragma once
#include "Entity.h"
#include "Node.h"
#include "RelationshipType.h"

class Relationship: public Entity 
{
public:
	virtual long getId() const override = 0;
	virtual void remove() = 0;
	virtual RelationshipType getType() const = 0;
	virtual bool isType(RelationshipType type) const = 0;
	virtual long getStartNodeId() const = 0;
	virtual long getEndNodeId() const = 0;
	virtual long getOtherNodeId(long id) const = 0;
};

