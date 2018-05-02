#include "CacheAccess.h"


CacheAccess::CacheAccess()
{
}


CacheAccess::~CacheAccess()
{
}

CacheAccess::CacheAccess(PropertyKeyTokenHolder *propertyKeyTokenHolder, RelationshipTypeTokenHolder *relationshipTypeTokenHolder, LabelTokenHolder *labelTokenHolder)
{
	this->propertyKeyTokenHolder = propertyKeyTokenHolder;
	this->labelTokenHolder = labelTokenHolder;
	this->relationshipTypeTokenHolder = relationshipTypeTokenHolder;
}
