#pragma once
#include "../../kernel/impl/util/Computer.h"
#include "PrimitiveLongArrayQueueIterator.h"
#include <stdexcept>


using namespace std;

class PrimitiveLongArrayQueue
{
public:
	PrimitiveLongArrayQueue();
	~PrimitiveLongArrayQueue();
	bool isEmpty() const;
	void clear();
	int size() const;
	void close();
	PrimitiveLongArrayQueueIterator iterator();
	long dequeue();
	void enqueue(long value);
	void ensureCapacity();

private:
	const static int DEFAULT_CAPACITY = 16;
	long *values;
	int head;
	int tail;
	int nowLenth;

	void initValues(int capacity);

};

