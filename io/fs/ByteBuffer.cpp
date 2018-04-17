#include "ByteBuffer.h"




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
}

void ByteBuffer::allocate(int capacity)
{
	try
	{
		if (capacity < 0) {
			throw new std::exception("error in buffer allocate.");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	// mark, pos, lim, cap, buf, offset
	ByteBuffer(-1, 0, capacity, capacity, new char[capacity], 0);
}

char * ByteBuffer::getBuf() const
{
	return this->buf;
}

void ByteBuffer::appendToBuf(char buf[])
{
	strcat(this->buf, buf);
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
	if (position >= limit)
	{
		throw new overflow_error("BufferOverflowException");
	}
	return position++;
}

int ByteBuffer::nextGetIndex(int nb)
{
	if (this->limit - this->position < nb)
	{
		throw new overflow_error("BufferOverflowException");
	}
	int p = position;
	position += nb;
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
