#pragma once
#include "StoreChannel.h"
#include <stdexcept>

class OffsetChannel:public StoreChannel
{
public:
	OffsetChannel();
	~OffsetChannel();
	OffsetChannel(StoreChannel *delegate, long offset);
	long offsetTo(long position);
	FileLock *tryLock() override;
	void writeAll(ByteBuffer *src, const long &position) override;
	void writeAll(ByteBuffer *src) override;
	int read(ByteBuffer *dst, const long &position) override;
	void readAll(ByteBuffer *dst) override;
	int read(ByteBuffer *dst) override;
	int write(ByteBuffer *src) override;
	long position();
	StoreChannel *position(const long &newPosition) override;
	long size() override;
	StoreChannel *truncate(const long &size) override;
	void flush() override;
	long write(ByteBuffer ** srcs) override;
	long write(ByteBuffer ** srcs, const int &offset, const int &length) override;
	long read(ByteBuffer ** dsts, const int &offset, const int &length) override;
	long read(ByteBuffer ** dsts) override;
	bool isOpen() override;
	void close() override;

private:
	StoreChannel *delegate;
	long offset;
};

