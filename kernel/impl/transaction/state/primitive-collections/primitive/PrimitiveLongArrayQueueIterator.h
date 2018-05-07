#pragma once
#include <stdexcept>

using namespace std;


class PrimitiveLongArrayQueueIterator
{
public:
	PrimitiveLongArrayQueueIterator();
	~PrimitiveLongArrayQueueIterator();

	PrimitiveLongArrayQueueIterator(int head);
	bool hasNext(const int &tail) const;
	long next(const int &tail, long values[], const int &nowLength);

private:
	int position;
};

