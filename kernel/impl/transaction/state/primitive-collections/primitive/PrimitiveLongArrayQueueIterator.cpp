#include "PrimitiveLongArrayQueueIterator.h"



PrimitiveLongArrayQueueIterator::PrimitiveLongArrayQueueIterator()
{
}


PrimitiveLongArrayQueueIterator::~PrimitiveLongArrayQueueIterator()
{
}

PrimitiveLongArrayQueueIterator::PrimitiveLongArrayQueueIterator(int head)
{
	this->position = head;
}
long PrimitiveLongArrayQueueIterator::next(const int &tail, long values[], const int &nowLength)
{
	if (hasNext(tail))
	{
		long value = values[this->position];
		this->position = (this->position + 1) & (nowLength - 1);
		return value;
	}
	throw new underflow_error("No Element in this queue.");
}
bool PrimitiveLongArrayQueueIterator::hasNext(const int &tail) const
{
	return this->position != tail;
}

