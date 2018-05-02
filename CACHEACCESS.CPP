#include "kernel\impl\core\CacheAccess.h"

CacheAccess::CacheAccess(PropertyKeyTokenHolder *propertyKeyTokenHolder, RelationshipTypeTokenHolder *relationshipTypeTokenHolder, LabelTokenHolder *labelTokenHolder)
{
	this->labelTokenHolder = labelTokenHolder;
	this->propertyKeyTokenHolder = propertyKeyTokenHolder;
	this->relationshipTypeTokenHolder = relationshipTypeTokenHolder;
}
