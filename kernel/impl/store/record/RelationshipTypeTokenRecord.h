#pragma once
#include "TokenRecord.h"

class RelationshipTypeTokenRecord: public TokenRecord
{
public:
	RelationshipTypeTokenRecord();
	~RelationshipTypeTokenRecord();
	RelationshipTypeTokenRecord(int id);
	TokenRecord initialize(bool inUse, int nameId);
	string simpleName();

};

