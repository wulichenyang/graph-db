#include "StoreChannel.h"



StoreChannel::StoreChannel()
{
}


StoreChannel::~StoreChannel()
{
}

StoreChannel::StoreChannel(const FileChannel & channel)
{
	this->channel = channel;
}

long StoreChannel::write(ByteBuffer ** srcs)
{
	return 0;
}

long StoreChannel::write(ByteBuffer ** srcs, const int & offset, const int & length)
{
	return 0;
}

void StoreChannel::writeAll(ByteBuffer * src, const long & position)
{

}

void StoreChannel::writeAll(ByteBuffer * src)
{
}

StoreChannel StoreChannel::truncate(const long & size)
{
	return StoreChannel();
}

StoreChannel StoreChannel::position(const int & newPosition)
{
	return StoreChannel();
}

int StoreChannel::read(ByteBuffer * dst, const long & position)
{
	return 0;
}

void StoreChannel::readAll(ByteBuffer * dst)
{
}

int StoreChannel::read(ByteBuffer * dst)
{
	return 0;
}

long StoreChannel::read(ByteBuffer ** dsts, const int & offset, const int & length)
{
	return 0;
}

long StoreChannel::position()
{
	return 0;
}

FileLock StoreChannel::tryLock()
{
	return FileLock();
}

bool StoreChannel::isOpen()
{
	return false;
}

long StoreChannel::read(ByteBuffer ** dsts)
{
	return 0;
}

int StoreChannel::write(ByteBuffer * src)
{
	return 0;
}

void StoreChannel::close()
{
}

long StoreChannel::size()
{
	return 0;
}

void StoreChannel::flush()
{
}
