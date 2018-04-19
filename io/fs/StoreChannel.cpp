#include "StoreChannel.h"



StoreChannel::StoreChannel()
{
}


StoreChannel::~StoreChannel()
{
}

StoreChannel::StoreChannel(FileChannel * channel)
{
	this->channel = channel;
}

StoreChannel::StoreChannel(StoreChannel * channel)
{
	this->channel = channel->channel;
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
	long filePosition = position;
	long expectedEndPosition = filePosition + src->getLimit() - src->getPosition();
	int bytesWritten;
	
	while ((filePosition += bytesWritten = channel->write(src, filePosition)) < expectedEndPosition)
	{
		if (bytesWritten < 0)
		{
			throw new runtime_error("Unable to write to disk, reported bytes written was " + bytesWritten);
		}
	}
}

void StoreChannel::writeAll(ByteBuffer * src)
{
	long bytesToWrite = src->getLimit() - src->getPosition();
	int bytesWritten;
	while ((bytesToWrite -= bytesWritten = write(src)) > 0)
	{
		if (bytesWritten < 0)
		{
			throw new runtime_error("Unable to write to disk, reported bytes written was " + bytesWritten);
		}
	}

}

StoreChannel * StoreChannel::truncate(const long & size)
{
	this->channel->truncate(size);
	return this;
}

StoreChannel * StoreChannel::position(const int & newPosition)
{
	this->channel->position(newPosition);
	return this;
}

int StoreChannel::read(ByteBuffer * dst, const long & position)
{
	return this->channel->read(dst, position);
}

int StoreChannel::read(ByteBuffer * dst)
{
	return this->channel->read(dst);
}

long StoreChannel::read(ByteBuffer ** dsts, const int & offset, const int & length)
{
	return 0;
}

void StoreChannel::readAll(ByteBuffer * dst)
{
	while (dst->hasRemaining()) {
		int bytesRead = channel->read(dst);
		if (bytesRead < 0)
		{
			throw new runtime_error("Channel has reached end-of-stream.");
		}
	}
} 

long StoreChannel::position()
{
	return this->channel->position();
}

FileLock * StoreChannel::tryLock()
{
	return new FileLock();
}

bool StoreChannel::isOpen()
{
	return this->channel->isOpen();
}

long StoreChannel::read(ByteBuffer ** dsts)
{
	return 0;
}

int StoreChannel::write(ByteBuffer * src)
{
	return this->channel->write(src);
}

void StoreChannel::close()
{
	this->channel->close();
}

long StoreChannel::size()
{
	return this->channel->size();
}

void StoreChannel::flush()
{
	this->channel->flush();
}
