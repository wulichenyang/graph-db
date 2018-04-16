#include "ByteBuffer.h"


ByteBuffer::ByteBuffer()
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
