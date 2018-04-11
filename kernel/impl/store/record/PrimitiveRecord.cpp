#include "PrimitiveRecord.h"



PrimitiveRecord::~PrimitiveRecord()
{
}

PrimitiveRecord::PrimitiveRecord(long id)
{
	__super::AbstractBaseRecord(id);
}

PrimitiveRecord::PrimitiveRecord(long id, long nextProp)
{
	__super::AbstractBaseRecord(id);
	this->nextProp = nextProp;
}

long PrimitiveRecord::getNextProp() const
{
	return 0;
}

void PrimitiveRecord::setNextProp(long nextProp)
{
}

void PrimitiveRecord::clear()
{
	__super::clear();
	nextProp = 
}
