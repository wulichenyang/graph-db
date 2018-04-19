#include "PrimitiveLongArrayQueue.h"
#include <cstring>


PrimitiveLongArrayQueue::PrimitiveLongArrayQueue()
{
	initValues(this->DEFAULT_CAPACITY);
}


PrimitiveLongArrayQueue::~PrimitiveLongArrayQueue()
{
	delete[]values;
}

bool PrimitiveLongArrayQueue::isEmpty() const
{
	return head == tail;
}

void PrimitiveLongArrayQueue::clear()
{
	initValues(DEFAULT_CAPACITY);
	nowLenth = DEFAULT_CAPACITY;
}

int PrimitiveLongArrayQueue::size() const
{
	return (tail - head) & (nowLenth - 1);;
}

void PrimitiveLongArrayQueue::close()
{
	values = new long[0];
}

PrimitiveLongArrayQueueIterator PrimitiveLongArrayQueue::iterator()
{
	return PrimitiveLongArrayQueueIterator();
}

long PrimitiveLongArrayQueue::dequeue()
{
	if (isEmpty())
	{
		throw new underflow_error("Fail to poll first element. Queue is empty.");
	}
	long value = values[head];
	head = (head + 1) & (nowLenth - 1);
	return value;
}

void PrimitiveLongArrayQueue::enqueue(long value)
{
	values[tail] = value;
	tail = (tail + 1) & (nowLenth - 1);
	if (tail == head)
	{
		// 队列满后，扩展为2倍队列空间
		ensureCapacity();
	}
}

void PrimitiveLongArrayQueue::ensureCapacity()
{
	int newLenth = nowLenth << 1;

	if (newLenth < 0) {
		throw new overflow_error("Fail to increase queue capacity.");
	}

	long *newValues = new long[newLenth];
	int elementsFromHeadTillEnd = this->nowLenth - head;
	// 复制头部部分
	memmove(newValues, values + head, (this->nowLenth - head) * sizeof(long));
	// 复制尾部部分
	memmove(newValues + (this->nowLenth - head), values, tail * sizeof(long));
	tail = this->nowLenth;
	head = 0;
	this->nowLenth = newLenth;
	delete[] values;
	// 指针指向新的动态区
	values = newValues;
}

void PrimitiveLongArrayQueue::addAll(PrimitiveLongArrayQueue * otherQueue)
{
	while (!otherQueue->isEmpty())
	{
		enqueue(otherQueue->dequeue());
	}
}

void PrimitiveLongArrayQueue::initValues(int capacity)
{
	values = new long[capacity];
	head = 0;
	tail = 0;
}
