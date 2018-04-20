#include "FreeIdKeeper.h"



FreeIdKeeper::FreeIdKeeper()
{
}


FreeIdKeeper::~FreeIdKeeper()
{
	delete freeIds;
	delete readFromDisk;
	delete channel;
}

FreeIdKeeper::FreeIdKeeper(StoreChannel * channel, int batchSize, bool aggressiveMode)
{
	this->channel = channel;
	// 自定义的阈值，freeId队列满足batchSize则进行写入磁盘
	this->batchSize = batchSize;
	this->aggressiveMode = aggressiveMode;

	this->initialPosition = channel->size();
	this->stackPosition = initialPosition;
	// 缓冲和磁盘上的freeId总数
	this->freeIdCount = stackPosition / ID_ENTRY_SIZE;
}

long FreeIdKeeper::countFreeIds(StoreChannel * channel)
{
	return channel->size() / ID_ENTRY_SIZE;
}

void FreeIdKeeper::freeId(long id)
{
	freeIds->enqueue(id);
	freeIdCount++;

	if (freeIds->size() >= batchSize)
	{
		// batchSize的Id通过ByteBuffer写入磁盘
		ByteBuffer * buf = new ByteBuffer()->allocate(batchSize * ID_ENTRY_SIZE);
		long endPosition = flushFreeIds(buf);
		if (aggressiveMode)
		{
			stackPosition = endPosition;
		}
		delete buf;
	}
}

void FreeIdKeeper::truncate(long position)
{
	try
	{
		channel->truncate(position);
	}
	catch (const runtime_error & e)
	{
		stringstream ss;
		ss << "Failed to truncate" << e.what();
		throw new runtime_error(ss.str());
	}
}

long FreeIdKeeper::getId()
{
	long result;
	if (freeIds->size() > 0 && aggressiveMode)
	{
		result = freeIds->dequeue();
		freeIdCount--;
	}
	else
	{
		result = getIdFromDisk();
		if (result != IdContainer::NO_RESULT)
		{
			freeIdCount--;
		}
	}
	return result;
}

long * FreeIdKeeper::getIds(int numberOfIds)
{
	if (freeIdCount == 0)
	{
		return new long[0];
	}
	int reusableIds = (int)fmin(numberOfIds, freeIdCount);
	long *ids = new long[reusableIds];
	int cursor = 0;
	while ((cursor < reusableIds) && !freeIds->isEmpty())
	{
		ids[cursor++] = freeIds->dequeue();
	}
	while (cursor < reusableIds)
	{
		ids[cursor++] = getIdFromDisk();
	}
	freeIdCount -= reusableIds;
	return ids;
}

long FreeIdKeeper::getCount()
{
	return freeIdCount;
}

long FreeIdKeeper::getIdFromDisk()
{
	if (readFromDisk->isEmpty())
	{
		readIdBatch();
	}
	if (!readFromDisk->isEmpty())
	{
		return readFromDisk->dequeue();
	}
	else
	{
		return IdContainer::NO_RESULT;
	}
}

void FreeIdKeeper::readIdBatch()
{
	try
	{
		readIdBatch0();
	}
	catch (const runtime_error & e)
	{
		throw new runtime_error("Failed reading free id batch");
	}
}

void FreeIdKeeper::readIdBatch0()
{
	if (stackPosition == 0)
	{
		return;
	}
	// startPosition 定位到-BatchSize位置（id足够）
	// startPosition 定位到 0(id不够)
	long startPosition = fmax(stackPosition - batchSize * ID_ENTRY_SIZE, 0);
	int bytesToRead = (int)(stackPosition - startPosition);
	ByteBuffer * readBuffer = new ByteBuffer() -> allocate(bytesToRead);

	channel->position(startPosition);
	channel->readAll(readBuffer);
	stackPosition = startPosition;

	readBuffer->flip();
	int idsRead = bytesToRead / ID_ENTRY_SIZE;
	for (int i = 0; i < idsRead; i++)
	{
		long id = readBuffer->getLong();
		readFromDisk->enqueue(id);
	}
	if (aggressiveMode)
	{
		truncate(startPosition);
	}
	delete readBuffer;
}

long FreeIdKeeper::flushFreeIds(ByteBuffer * writeBuffer)
{
	try
	{
		return flushFreeIds0(writeBuffer);
	}
	catch (const runtime_error & e)
	{
		throw new runtime_error("Unable to write free id batch");
	}
}

long FreeIdKeeper::flushFreeIds0(ByteBuffer * writeBuffer)
{
	channel->position(channel->size());
	writeBuffer->clear();
	while (!(freeIds->isEmpty()))
	{
		long id = freeIds->dequeue();
		if (id == IdContainer::NO_RESULT)
		{
			continue;
		}
		writeBuffer->putLong(id);
		if (writeBuffer->getPosition() == writeBuffer->getCapacity())
		{
			writeBuffer->flip();
			channel->writeAll(writeBuffer);
			writeBuffer->clear();
		}
	}
	writeBuffer->flip();
	if (writeBuffer->hasRemaining())
	{
		channel->writeAll(writeBuffer);
	}
	delete writeBuffer;
	return channel->position();
}

void FreeIdKeeper::close()
{
	ByteBuffer *writeBuffer = new ByteBuffer()->allocate(batchSize * ID_ENTRY_SIZE);
	flushFreeIds(writeBuffer);
	freeIds->addAll(readFromDisk);
	flushFreeIds(writeBuffer);
	if (!aggressiveMode)
	{
		compact(writeBuffer);
	}
	channel->flush();
	delete writeBuffer;
}

void FreeIdKeeper::compact(ByteBuffer * writeBuffer)
{
	assert(stackPosition <= initialPosition); // the stack can only be consumed in regular mode
	if (initialPosition == stackPosition)
	{
		// there is no compaction to be done
		return;
	}

	long writePosition = stackPosition;
	long readPosition = initialPosition; // readPosition to end of file contain new free IDs, to be compacted
	int nBytes;
	do
	{
		writeBuffer->clear();
		channel->position(readPosition);
		nBytes = channel->read(writeBuffer);

		if (nBytes > 0)
		{
			readPosition += nBytes;

			writeBuffer->flip();
			channel->position(writePosition);
			channel->writeAll(writeBuffer);
			writePosition += nBytes;
		}
	} while (nBytes > 0);

	channel->truncate(writePosition);
}
