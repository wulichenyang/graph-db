#pragma once
#include "RelationshipTypeTokenHolder.h"
#include "PropertyKeyTokenHolder.h"
#include "LabelTokenHolder.h"

class CacheAccess
{
public:
	CacheAccess();
	~CacheAccess();
	CacheAccess(
		PropertyKeyTokenHolder *propertyKeyTokenHolder,
		RelationshipTypeTokenHolder *relationshipTypeTokenHolder,
		LabelTokenHolder *labelTokenHolder);

private:
	PropertyKeyTokenHolder *propertyKeyTokenHolder;
	RelationshipTypeTokenHolder *relationshipTypeTokenHolder;
	LabelTokenHolder *labelTokenHolder;
};

