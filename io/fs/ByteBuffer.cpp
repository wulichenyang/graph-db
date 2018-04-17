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

ByteBuffer * ByteBuffer::clear()
{
	this->position = 0;
	this->mark = -1;
	this->limit = this->capacity;
	return nullptr;
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
