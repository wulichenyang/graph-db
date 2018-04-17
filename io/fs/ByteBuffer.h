#pragma once
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class ByteBuffer
{
public:
	int offset;

	ByteBuffer(int mark, int pos, int lim, int cap,   // package-private
		char * buf, int offset);
	ByteBuffer(int mark, int pos, int lim, int cap);
	~ByteBuffer();

	void allocate(int capacity);
	char* getBuf() const;
	void setBuf(char *buf);
	// append a char[] which has a '\0' into this->buf.
	void appendToBuf(char buf[]);

	int getCapacity() const;
	int getPosition() const;
	int getLimit() const;
	ByteBuffer *setPosition(int newPosition);
	ByteBuffer *setLimit(int newLimit);

	/**
	* Clears this buffer.  The position is set to zero, the limit is set to
	* the capacity, and the mark is discarded.
	*
	* <p> Invoke this method before using a sequence of channel-read or
	* <i>put</i> operations to fill this buffer.
	*/
	ByteBuffer *clear();

	/**
	* Flips this buffer.  The limit is set to the current position and then
	* the position is set to zero.  If the mark is defined then it is
	* discarded.
	*
	* <p> After a sequence of channel-read or <i>put</i> operations, invoke
	* this method to prepare for a sequence of channel-write or relative
	* <i>get</i> operations. 
	*/
	ByteBuffer *flip();

	/**
	* Rewinds this buffer.  The position is set to zero and the mark is
	* discarded.
	*
	* <p> Invoke this method before a sequence of channel-write or <i>get</i>
	* operations, assuming that the limit has already been set
	* appropriately.  For example:
	*/
	ByteBuffer *rewind();

	char get();
	ByteBuffer *put(const char &b);
	char get(const int &index);
	ByteBuffer *put(const int &index, const char &b);
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
	int mark = -1;
	int position = 0;
	int capacity;
	int limit;
	int offset;
};

