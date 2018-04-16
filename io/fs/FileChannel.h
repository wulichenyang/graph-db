#pragma once
#include <stdio.h>
#include "../lock/FileLock.h"
class FileChannel
{
public:
	FileChannel();
	~FileChannel();
	static FileChannel open(char*path, char * mode);
	bool writeToFile(char nChar[], int length);
	FILE * getFilePointer();

	// -- Channel operations --

	/**
	* Reads a sequence of bytes from this channel into the given buffers.
	*/
	int read(char *dst);
	long read(char *dst, int offset, int length);
	/**
	* Reads a sequence of bytes from this channel into the given buffer,
	* starting at the given file position.
	*/
	int read(char *dst, long position);

	/**
	* Writes a sequence of bytes to this channel from the given buffers.
	*/
	int write(char *src);
	long write(char *src, int offset, int length);

	/**
	* Writes a sequence of bytes to this channel from the given buffer,
	* starting at the given file position.
	*/
	int write(char *src, long position);

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
	FileChannel position(long newPosition);

	/**
	* Returns the current size of this channel's file.
	*/
	long size();

	/**
	* Truncates this channel's file to the given size.
	*/
	FileChannel truncate(long size);

	/**
	* Forces any updates to this channel's file to be written to the storage
	* device that contains it.
	*/
	void flush();

	/**
	* Acquires a lock on the given region of this channel's file.
	*/
	FileLock tryLock();

	/**
	* Closes this channel.
	*
	* <p> If the channel has already been closed then this method returns
	* immediately.  Otherwise it marks the channel as closed and then invokes
	* the {@link #implCloseChannel implCloseChannel} method in order to
	* complete the close operation.  </p>
	*/
	void close();

	bool isOpen();

private:
	FILE * pFile;  //Òþ²ØÊµÏÖÏ¸½Ú
	char * path;
	char * modeAttribute;
	bool open = true;
};

