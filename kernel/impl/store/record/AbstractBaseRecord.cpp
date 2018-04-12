#include "AbstractBaseRecord.h"



AbstractBaseRecord::AbstractBaseRecord()
{
}

AbstractBaseRecord::AbstractBaseRecord(long id)
{
	this->id = id;
	clear();
}


AbstractBaseRecord::~AbstractBaseRecord()
{
}

void AbstractBaseRecord::clear()
{
	inUseFlag = false;
	created = false;
}

long AbstractBaseRecord::getId() const
{
	return id;
}

void AbstractBaseRecord::setId(long id)
{
	this->id = id;
}

bool AbstractBaseRecord::inUse() const
{
	return inUseFlag;
}

void AbstractBaseRecord::setInUse(bool inUse)
{
	inUseFlag = inUse;
}

void AbstractBaseRecord::setCreated()
{
	created = true;
}

bool AbstractBaseRecord::isCreated() const
{
	return created;
}

AbstractBaseRecord AbstractBaseRecord::initialize(bool inUse)
{
	inUseFlag = inUse;
	created = false;
	return *this;
}
