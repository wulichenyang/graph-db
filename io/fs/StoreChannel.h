#pragma once
#include <stdio.h>
#include "FileChannel.h"

class StoreChannel
{
public:
	StoreChannel();
	virtual ~StoreChannel();
	StoreChannel(FileChannel * channel);
	StoreChannel(StoreChannel * channel);

	virtual long write(ByteBuffer ** srcs);
	virtual long write(ByteBuffer ** srcs, const int &offset, const int &length);
	virtual void writeAll(ByteBuffer *src, const long &position);
	virtual void writeAll(ByteBuffer *src);
	virtual StoreChannel *truncate(const long &size);
	virtual StoreChannel *position(const long &newPosition);
	virtual int read(ByteBuffer *dst, const long &position);
	virtual void readAll(ByteBuffer *dst);
	virtual int read(ByteBuffer *dst);
	virtual long read(ByteBuffer ** dsts, const int &offset, const int &length);
	virtual long position();
	virtual FileLock * tryLock();
	virtual bool isOpen();
	virtual long read(ByteBuffer **dsts);
	virtual int write(ByteBuffer *src);
	virtual void close();
	virtual long size();
	virtual void flush();

private:
	FileChannel *channel;
};

