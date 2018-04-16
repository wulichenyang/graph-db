#pragma once
#include <stdexcept>
#include <iostream>
#include <string.h>

class ByteBuffer
{
public:
	int offset;

	ByteBuffer();
	~ByteBuffer();

	void allocate(int capacity);
	char* getBuf() const;
	void setBuf(char *buf);
	void appendToBuf(char buf[]);

	int getCapacity() const;
	int getPosition() const;

	ByteBuffer *toPosition(int newPosition);
	ByteBuffer *clear();
	ByteBuffer *rewind();

	unsigned char get();
	ByteBuffer *put(const unsigned char &b);
	unsigned char get(const int &index);
	ByteBuffer *put(const int &index, const unsigned char &b);
	ByteBuffer *get(char *dst, const int &offset, const int &length);
	ByteBuffer *get(char* dst);
	ByteBuffer *put(char* src, const int &offset, const int &length);
	ByteBuffer *put(char* src);
	int getInt();
	ByteBuffer *putInt(const int &value);
	int getInt(const int &index);
	ByteBuffer *putInt(const int &index, const int &value);
	long getLong();
	ByteBuffer *putLong(const long &value);
	long getLong(const int &index);
	ByteBuffer *putLong(const int &index, const long &value);

private:
	char * buf;
	int position = 0;
	int capacity;
	int offset;
};

