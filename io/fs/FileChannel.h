#pragma once
#include <stdio.h>
#include "../lock/FileLock.h"
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "ByteBuffer.h"
#include <mutex>

#define BUF_SIZE 1024

using namespace std;

class FileChannel
{
public:
	FileChannel();
	~FileChannel();
	FileChannel(char *storeDir, const char *fileName);
	FileChannel(char *path);
	FileChannel *open(char *mode);
	char * getParentFile();
	FILE * getFilePtr();
	char * getFileName();
	char * getMode();
	// -- Channel operations --

	/**
	* Reads a sequence of bytes from this channel into the given buffers.
	*/
	int read(ByteBuffer *dst);
	long read(ByteBuffer **dst, int offset, int length);
	/**
	* Reads a sequence of bytes from this channel into the given buffer,
	* starting at the given file position.
	*/
	int read(ByteBuffer *dst, long position);

	/**
	* Writes a sequence of bytes to this channel from the given buffers.
	*/
	int write(ByteBuffer *src);
	long write(ByteBuffer **src, int offset, int length);

	/**
	* Writes a sequence of bytes to this channel from the given buffer,
	* starting at the given file position.
	*/
	int write(ByteBuffer *src, long position);

	// -- Other operations --

	/**
	* Returns this channel's file position.
	*
	* @return  This channel's file position,
	*          a non-negative integer counting the number of bytes
	*          from the beginning of the file to the current position
	*/
	long position();

	/**
	* Sets this channel's file position.
	*/
	FileChannel *position(long newPosition);

	/**
	* Returns the current size of this channel's file.
	*/
	long size();

	/**
	* Truncates this channel's file to the given size.
	*
	* <p> If the given size is less than the file's current size then the file
	* is truncated, discarding any bytes beyond the new end of the file.  If
	* the given size is greater than or equal to the file's current size then
	* the file is not modified.  In either case, if this channel's file
	* position is greater than the given size then it is set to that size.
	* </p>
	*/
	FileChannel *truncate(long size);

	/**
	* Forces any updates to this channel's file to be written to the storage
	* device that contains it.
	*/
	void flush();

	/**
	* Acquires a lock on the given region of this channel's file.
	*/
	FileLock *tryLock();

	/**
	* ͬ���رգ�to be con��
	* Closes this channel.
	*
	* <p> If the channel has already been closed then this method returns
	* immediately.  Otherwise it marks the channel as closed and then invokes
	* the {@link #implCloseChannel implCloseChannel} method in order to
	* complete the close operation.  </p>
	*/
	void close();

	bool isOpen();
	bool fileExists();

private:
	//file pointer
	FILE * pFile;  
	char * path;
	char * mode;
	bool ifOpen;
	char *storeDir;
	mutex closeMutex;
};

