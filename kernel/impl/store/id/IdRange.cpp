#include "IdRange.h"
#include "../../util/Computer.h"


IdRange::IdRange()
{
}


IdRange::IdRange(long * defragIds, long rangeStart, int rangeLength)
{
	this->defragIds = defragIds;
	this->rangeStart = rangeStart;
	this->rangeLength = rangeLength;
}

IdRange::~IdRange()
{
	delete defragIds;
}

long * IdRange::getDefragIds()
{
	return defragIds;
}

long IdRange::getRangeStart()
{
	return rangeStart;
}

int IdRange::getRangeLength()
{
	return rangeLength;
}

string IdRange::toString()
{
	return "IdRange";
}

int IdRange::totalSize()
{
	return Computer::arrayLen(defragIds) + rangeLength;
}

long IdRange::getHighId()
{
	return  rangeStart + rangeLength;
}
