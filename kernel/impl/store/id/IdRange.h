#pragma once
#include <string>
using namespace std;

class IdRange
{
public:
	IdRange();
	IdRange(long * defragIds, long rangeStart, int rangeLength);
	~IdRange();
	long * getDefragIds();
	long getRangeStart();
	int getRangeLength();
	string toString();
	int totalSize();
	long getHighId();

private:
	long * defragIds;
	long rangeStart;
	int rangeLength;
};

