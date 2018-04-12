#pragma once
#include "TokenRecord.h"
class LabelTokenRecord: public TokenRecord
{
public:
	LabelTokenRecord();
	~LabelTokenRecord();
	LabelTokenRecord(int id);
	TokenRecord initialize(bool inUse, int nameId);
	string simpleName() const override;
};

