#include "RelationshipTypeTokenRecord.h"



RelationshipTypeTokenRecord::RelationshipTypeTokenRecord()
{
}


RelationshipTypeTokenRecord::~RelationshipTypeTokenRecord()
{
}

RelationshipTypeTokenRecord::RelationshipTypeTokenRecord(int id)
	:TokenRecord(id)
{
}

TokenRecord RelationshipTypeTokenRecord::initialize(bool inUse, int nameId)
{
	TokenRecord::initialize(inUse, nameId);
	return *this;
}

string RelationshipTypeTokenRecord::simpleName()
{
	return "RelationshipType";
}
