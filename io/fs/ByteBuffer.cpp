#include "ByteBuffer.h"




ByteBuffer::ByteBuffer()
{
}

ByteBuffer::ByteBuffer(int mark, int pos, int lim, int cap, char * buf, int offset)
{
	try
	{
		if (cap < 0) 
		{
			stringstream ss;
			ss << "Negative capacity : " << cap << endl;
			throw new invalid_argument(ss.str());
		}
		this->capacity = cap;

		setLimit(lim);
		setPosition(pos);

		if (mark >= 0) {
			if (mark > pos)
			{
				stringstream ss;
				ss << "mark > position: ("
					<< mark << pos << ")" << endl;
				throw new invalid_argument(ss.str());
			}
			this->mark = mark;
		}
	}
	catch (const std::invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	this->buf = buf;
	this->offset = offset;
}

ByteBuffer::ByteBuffer(int mark, int pos, int lim, int cap)
{
	ByteBuffer(mark, pos, lim, cap, NULL, 0);
}

ByteBuffer::~ByteBuffer()
{
	delete[]this->buf;
}

ByteBuffer* ByteBuffer::allocate(int capacity)
{
	try
	{
		if (capacity < 0) {
			throw new invalid_argument("error in buffer allocate.");
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << e.what() << std::endl;
	}
	// mark, pos, lim, cap, buf, offset
	ByteBuffer(-1, 0, capacity, capacity, new char[capacity], 0);
	return this;
}

//char * ByteBuffer::readBuf(int nb)
//{
//	try
//	{
//		if (nb < 0 || nb + this->position > this->limit) {
//			throw new out_of_range("nb < 0 || nb + this->position > this-> limit");
//		}
//	}
//	catch (const std::out_of_range& e)
//	{
//		cout << e.what() << endl;
//	}
//
//	int p = this->position;
//	this->position += nb;
//	return (this->buf + p);
//}

void ByteBuffer::nextReadBufSeq(const int & nb)
{
	try
	{
		if (nb < 0 || nb + this->position > this->limit) {
			throw new out_of_range("nb < 0 || nb + this->position > this-> limit");
		}
	}
	catch (const std::out_of_range& e)
	{
		cout << e.what() << endl;
	}
	// update position
	this->position += nb;
}

// next bufSize bytes to write
char * ByteBuffer::nextWriteBufSeq(int * realOffSize)
{
	int p = this->position;
	if (this->position + BUF_SIZE > this->limit) {
		*realOffSize = this->limit - this->position;
		this->position = this->limit;
		return this->buf + p;
	}
	*realOffSize = BUF_SIZE;
	this->position += BUF_SIZE;
	return this->buf + p;
}


void ByteBuffer::appendToBuf(char buf[])
{
	strcat(this->buf, buf);
	try {
		if (this->position + strlen(buf) > this->limit) 
		{
			throw new out_of_range("position > limit");
		}
	}
	catch (const out_of_range & e)
	{
		cout << e.what() << endl;
	}
	this->position += strlen(buf);
}

int ByteBuffer::getCapacity() const
{
	return this->capacity;
}

int ByteBuffer::getPosition() const
{
	return this->position;
}

int ByteBuffer::getLimit() const
{
	return this->limit;
}

ByteBuffer * ByteBuffer::setPosition(int newPosition)
{
	if ((newPosition > this->limit) || (newPosition < 0))
	{
		throw new invalid_argument("pos > limit or pos < 0");
	}
	this->position = newPosition;

	if (this->mark > this->position)
	{
		this->mark = -1;
	}
	return this;
}

ByteBuffer * ByteBuffer::setLimit(int newLimit)
{
	if ((newLimit > this->capacity) || (newLimit < 0))
	{
		throw new invalid_argument("lim > capacity or < 0");
	}

	this->limit = newLimit;

	if (this->position > this->limit)
	{
		this->position = this->limit;
	}

	if (this->mark > this->limit)
	{
		this->mark = -1;
	}
	return this;
}

ByteBuffer * ByteBuffer::setMark()
{
	this->mark = this->position;
	return this;
}

ByteBuffer * ByteBuffer::reset()
{
	int m = mark;
	if (m < 0)
		throw new runtime_error("InvalidMarkException");
	this->position = m;
	return this;
}

ByteBuffer * ByteBuffer::clear()
{
	this->position = 0;
	this->mark = -1;
	this->limit = this->capacity;
	return this;
}

ByteBuffer * ByteBuffer::flip()
{
	this->limit = position;
	this->position = 0;
	mark = -1;
	return this;
}

ByteBuffer * ByteBuffer::rewind()
{
	this->position = 0;
	this->mark = -1;
	return this;
}

int ByteBuffer::remaining()
{
	return this->limit - this->position;
}

bool ByteBuffer::hasRemaining()
{
	return this->position < this->limit;
}

int ByteBuffer::markValue()
{
	return this->mark;
}

void ByteBuffer::truncate()
{
	this->mark = -1;
	this->position = 0;
	this->limit = 0;
	this->capacity = 0;
}

void ByteBuffer::discardMark()
{
	this->mark = -1;
}

int ByteBuffer::nextGetIndex()
{
	if (this->position >= this->limit)
	{
		throw new overflow_error("BufferOverflowException");
	}
	return this->position++;
}

int ByteBuffer::nextGetIndex(int nb)
{
	if (this->limit - this->position < nb)
	{
		throw new overflow_error("BufferOverflowException");
	}
	int p = this->position;
	this->position += nb;
	return p;
}

int ByteBuffer::nextPutIndex()
{
	if (position >= limit)
	{
		throw new overflow_error("BufferOverflowException");
	}
	return position++;
}

int ByteBuffer::nextPutIndex(int nb)
{
	if (this->limit - this->position < nb)
	{
		throw new overflow_error("BufferOverflowException");
	}
	int p = position;
	position += nb;
	return p;
}

int ByteBuffer::checkIndex(int i)
{
	if ((i < 0) || (i >= limit)) {
		throw out_of_range("IndexOutOfBoundsException");
	}
	return i;
}

int ByteBuffer::checkIndex(int i, int nb)
{
	if ((i < 0) || (nb > limit - i)) 
	{
		throw out_of_range("IndexOutOfBoundsException");
	}
	return i;
}

void ByteBuffer::checkBounds(int off, int len, int size)
{
	if ((off | len | (off + len) | (size - (off + len))) < 0) 
	{
		throw new runtime_error("IndexOutOfBoundsException");
	}
}

int ByteBuffer::ix(const int &i)
{
	return i + this->offset;
}

long ByteBuffer::getLong()
{
	return *(long*)(this->buf + ix(nextGetIndex(8)));
}

ByteBuffer * ByteBuffer::putLong(const long & value)
{
	*(long*)(this->buf + ix(nextPutIndex(8))) = value;
	return this;
}

long ByteBuffer::getLong(const int & index)
{
	return *(long*)(this->buf + ix(checkIndex(index, 8)));
}

ByteBuffer * ByteBuffer::putLong(const int & index, const long & value)
{
	*(long*)(this->buf + ix(checkIndex(index, 8))) = value;
	return this;
}

char ByteBuffer::get()
{
	return this->buf[ix(nextGetIndex())];
}

char ByteBuffer::get(const int & i)
{
	return this->buf[ix(nextGetIndex(i))];
}

ByteBuffer * ByteBuffer::put(const int & index, const char & b)
{
	this->buf[ix(nextPutIndex(index))] = b;
	return this;
}

ByteBuffer * ByteBuffer::put(const char & b)
{
	this->buf[ix(nextPutIndex())] = b;
	return this;
}

int ByteBuffer::getInt()
{
	return *(int*)(this->buf + ix(nextGetIndex(4)));
}

ByteBuffer * ByteBuffer::putInt(const int & value)
{
	*(int*)(this->buf + ix(nextPutIndex(4))) = value;
	return this;
}

int ByteBuffer::getInt(const int & index)
{
	return *(int*)(this->buf + ix(checkIndex(index, 4)));
}

ByteBuffer * ByteBuffer::putInt(const int & index, const int & value)
{
	*(int*)(this->buf + ix(checkIndex(index, 4))) = value;
	return this;
}
