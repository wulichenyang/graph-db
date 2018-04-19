#pragma once
#include <stdio.h>
#include "FileChannel.h"

class StoreChannel
{
public:
	StoreChannel();
	~StoreChannel();
	StoreChannel(FileChannel * channel);

	long write(ByteBuffer ** srcs);
	long write(ByteBuffer ** srcs, const int &offset, const int &length);
	void writeAll(ByteBuffer *src, const long &position);
	void writeAll(ByteBuffer *src);
	StoreChannel *truncate(const long &size);
	StoreChannel *position(const int &newPosition);
	int read(ByteBuffer *dst, const long &position);
	void readAll(ByteBuffer *dst);
	int read(ByteBuffer *dst);
	long read(ByteBuffer ** dsts, const int &offset, const int &length);
	long position();
	FileLock * tryLock();
	bool isOpen();
	long read(ByteBuffer **dsts);
	int write(ByteBuffer *src);
	void close();
	long size();
	void flush();

private:
	FileChannel *channel;
};

