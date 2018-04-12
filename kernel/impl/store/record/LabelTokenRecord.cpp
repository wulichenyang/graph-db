#include "LabelTokenRecord.h"



LabelTokenRecord::LabelTokenRecord()
{
}


LabelTokenRecord::~LabelTokenRecord()
{
}

LabelTokenRecord::LabelTokenRecord(int id)
	:TokenRecord(id)
{
}

TokenRecord LabelTokenRecord::initialize(bool inUse, int nameId)
{
	TokenRecord::initialize(inUse, nameId);
	return *this;
}

string LabelTokenRecord::simpleName() const
{
	return "Label";
}
