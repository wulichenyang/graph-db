#pragma once
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <sstream>

#define BUF_SIZE 1024

using namespace std;

class ByteBuffer
{
public:
	ByteBuffer();
	ByteBuffer(int mark, int pos, int lim, int cap,   // package-private
		char * buf, int offset);
	ByteBuffer(int mark, int pos, int lim, int cap);
	~ByteBuffer();

	ByteBuffer* allocate(int capacity);
	//char* readBuf(int nb);
	void nextReadBufSeq(const int &nb);
	char* nextWriteBufSeq(int *realReadSize);
	void setBuf(char *buf);
	// append a char[] which has a '\0' into this->buf.
	void appendToBuf(char buf[]);

	int getCapacity() const;
	int getPosition() const;
	int getLimit() const;

	/**
	* Sets this buffer's position.  If the mark is defined and larger than the
	* new position then it is discarded.
	*/
	ByteBuffer *setPosition(int newPosition);

	/**
	* Sets this buffer's limit.  If the position is larger than the new limit
	* then it is set to the new limit.  If the mark is defined and larger than
	* the new limit then it is discarded.
	*/
	ByteBuffer *setLimit(int newLimit);

	/**
	* Sets this buffer's mark at its position.
	*/
	ByteBuffer *setMark();

	/**
	* Resets this buffer's position to the previously-marked position.
	*/
	ByteBuffer *reset();

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
	* appropriately.  
	*/
	ByteBuffer *rewind();

	/**
	* Returns the number of elements between the current position and the
	* limit.
	*
	* @return  The number of elements remaining in this buffer
	*/
	int remaining();
	/**
	* Tells whether there are any elements between the current position and
	* the limit.
	*
	* @return  <tt>true</tt> if, and only if, there is at least one element
	*          remaining in this buffer
	*/
	bool hasRemaining();

	int markValue();
	void truncate();
	void discardMark();

	// -- Package-private methods for bounds checking, etc. --

	/**
	* Checks the current position against the limit, throwing a {@link
	* BufferUnderflowException} if it is not smaller than the limit, and then
	* increments the position.
	*
	* @return  The current position value, before it is incremented
	*/
	int nextGetIndex();
	int nextGetIndex(int nb);

	/**
	* Checks the current position against the limit, throwing a {@link
	* BufferOverflowException} if it is not smaller than the limit, and then
	* increments the position.
	*
	* @return  The current position value, before it is incremented
	*/
	int nextPutIndex();
	int nextPutIndex(int nb);

	/**
	* Checks the given index against the limit, throwing an {@link
	* IndexOutOfBoundsException} if it is not smaller than the limit
	* or is smaller than zero.
	*/
	int checkIndex(int i);
	int checkIndex(int i, int nb);

	static void checkBounds(int off, int len, int size);

	// -- get put methods --
	int ix(const int &i);
	char get();
	char get(const int &index);

	ByteBuffer *put(const char &b);
	ByteBuffer *put(const int &index, const char &b);
	ByteBuffer *get(char * dst, const int &offset, const int &length);
	ByteBuffer *get(char * dst);
	ByteBuffer *put(char * src, const int &offset, const int &length);
	ByteBuffer *put(char * src);

	int getInt();
	ByteBuffer *putInt(const int &value);
	int getInt(const int &index);
	ByteBuffer *putInt(const int &index, const int &value);
	long getLong();
	ByteBuffer *putLong(const long &value);
	long getLong(const int &index);
	ByteBuffer *putLong(const int &index, const long &value);

private:
	// store data in bytes
	char * buf;
	// mark a index for the position to return
	int mark = -1;
	// read or put cursor position
	int position = 0;
	// allocated size of this buf
	int capacity;
	// read/write limitation index of this buf
	int limit;
	// offset from this position or from the beginning
	int offset;
};

