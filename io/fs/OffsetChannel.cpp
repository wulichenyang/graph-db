#include "OffsetChannel.h"


OffsetChannel::OffsetChannel()
{
}


OffsetChannel::~OffsetChannel()
{
	delete delegate;
}

OffsetChannel::OffsetChannel(StoreChannel * delegate, long offset)
{
	this->delegate = delegate;
	this->offset = offset;
}

long OffsetChannel::offsetTo(long position)
{
	if (position < 0)
	{
		throw new invalid_argument("Position must be >= 0.");
	}
	long r = position + offset;
	// HD 2-12 Overflow iff both arguments have the opposite sign of the result
	if (((position ^ r) & (offset ^ r)) < 0) {
		throw new overflow_error("long overflow");
	}
	return r;
}

FileLock *OffsetChannel::tryLock()
{
	return delegate->tryLock();
}

void OffsetChannel::writeAll(ByteBuffer * src, const long &position)
{
	delegate->writeAll(src, offsetTo(position));
}

void OffsetChannel::writeAll(ByteBuffer * src)
{
	delegate->writeAll(src);
}

int OffsetChannel::read(ByteBuffer * dst, const long & position)
{
	return delegate->read(dst, offsetTo(position));
}

void OffsetChannel::readAll(ByteBuffer * dst)
{
	delegate->readAll(dst);
}

int OffsetChannel::read(ByteBuffer * dst)
{
	return delegate->read(dst);
}

int OffsetChannel::write(ByteBuffer * src)
{
	return delegate->write(src);
}

long OffsetChannel::position()
{
	return delegate->position() - offset;
}

StoreChannel *OffsetChannel::position(const long &newPosition)
{
	return delegate->position(offsetTo(newPosition));
}

long OffsetChannel::size()
{
	return delegate->size() - offset;
}

StoreChannel *OffsetChannel::truncate(const long &size)
{
	delegate->truncate(offsetTo(size));
}

void OffsetChannel::flush()
{
	delegate->flush();
}

long OffsetChannel::write(ByteBuffer ** srcs)
{
	return delegate->write(srcs);
}

long OffsetChannel::write(ByteBuffer ** srcs, const int &offset, const int &length)
{
	return delegate->write(srcs, offset, length);
}

long OffsetChannel::read(ByteBuffer ** dsts, const int &offset, const int &length)
{
	return delegate->read(dsts, offset, length);
}

long OffsetChannel::read(ByteBuffer ** dsts)
{
	return delegate->read(dsts);
}

bool OffsetChannel::isOpen()
{
	return delegate->isOpen();
}

void OffsetChannel::close()
{
	delegate->close();
}

