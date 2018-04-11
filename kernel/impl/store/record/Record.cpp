#include "Record.h"


Record::Record(RecEnum type) {
	state = type;
}

Record::~Record() {}

void Record::setType(RecEnum type)
{
	state = type;
}

Record::RecEnum Record::getType() const
{
	return state;
}

int Record::getIntType() const
{
	return state;
}

long Record::getLongType() const
{
	return state;
}

char Record::getByteType() const
{
	return state;
}

bool Record::is(long value) const
{
	return value == (this->getLongType());
}
