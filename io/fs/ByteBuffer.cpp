#include "ByteBuffer.h"




ByteBuffer::ByteBuffer(int mark, int pos, int lim, int cap, char * buf, int offset)
{
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

	this->buf = new char[capacity];

	this->position = 0;
	this->capacity = capacity;
	this->offset = 0;
}

char * ByteBuffer::getBuf() const
{
	return this->buf;
}

void ByteBuffer::appendToBuf(char buf[])
{
	strcat(this->buf, buf);
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
