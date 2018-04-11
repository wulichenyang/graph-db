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
	return nextProp;
}

void PrimitiveRecord::setNextProp(long nextProp)
{
	this->nextProp = nextProp;
}

void PrimitiveRecord::clear()
{
	__super::clear();
	nextProp = (Record(Record::NOT_IN_USE)).getIntType();
}
