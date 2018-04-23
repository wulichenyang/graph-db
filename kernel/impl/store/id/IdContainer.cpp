#include "IdContainer.h"



IdContainer::IdContainer()
{
}

IdContainer::IdContainer(FileChannel *file, int grabSize, bool aggressiveReuse)
{
	if (grabSize < 1)
	{
		throw new invalid_argument("Illegal grabSize");
	}
	this->file = file;
	this->grabSize = grabSize;
	this->aggressiveReuse = aggressiveReuse;
}


IdContainer::~IdContainer()
{
	delete file;
	delete fileChannel;
	delete freeIdKeeper;

}

bool IdContainer::init()
{
	bool result = true;
	try
	{
		// 文件不存在 新建文件
		if (!(file->fileExists()))
		{
			createEmptyIdFile(file, 0, false);
			result = false;
		}
		// 存在则打开文件
		fileChannel = new StoreChannel(file->open("r+"));
		// 读取文件中的 highId
		initialHighId = readAndValidateHeader();
		markAsSticky();

		this->freeIdKeeper = new FreeIdKeeper(new OffsetChannel(fileChannel, HEADER_SIZE), grabSize, aggressiveReuse);
		closed = false;
	}
	catch (const runtime_error &e)
	{
		throw new runtime_error("Unable to init id file ");
	}
	return result;
}

bool IdContainer::isClosed()
{
	return close;
}

long IdContainer::getInitialHighId()
{
	return initialHighId;
}

void IdContainer::assertStillOpen()
{
	if (closed)
	{
		throw new runtime_error("Closed id file ");
	}
}

void IdContainer::createEmptyIdFile(FileChannel * file, const long & highId, const bool & throwIfFileExists)
{
	if (file == NULL) {
		throw new invalid_argument("Null fileChannel");
	}
	if (throwIfFileExists && file->fileExists()) {
		stringstream ss;
		ss << "Can't create id file [" <<
			file << "], file already exists";
		throw new runtime_error(ss.str());
	}
	try
	{
		StoreChannel *channel = new StoreChannel(file->open("w+"));
		// write the header
		channel->truncate(0);
		ByteBuffer *buffer = new ByteBuffer()->allocate(HEADER_SIZE);
		buffer->put(CLEAN_GENERATOR)->putLong(highId)->flip();
		channel->writeAll(buffer);
		channel->flush();

		delete channel;
		delete buffer;
	}
	catch (const runtime_error &e)
	{
		throw new runtime_error("Unable to create id file ");
	}
}

string IdContainer::toString()
{
	stringstream ss;
	ss << "IdContainer{" << "file=" << file->getFileName() << ", defragCount=" <<
		freeIdKeeper->getCount() << ", grabSize=" << grabSize << ", aggressiveReuse=" <<
		aggressiveReuse << ", closed=" << closed << '}';
	return ss.str();
}

long IdContainer::readAndValidateHeader()
{
	try
	{
		return readAndValidate(fileChannel, file);
	}
	catch (const runtime_error &e)
	{
		fileChannel->close();
		throw e;
	}
}

long IdContainer::readAndValidate(StoreChannel * channel, FileChannel * fileName)
{
	ByteBuffer *buffer = new ByteBuffer->allocate(HEADER_SIZE);
	readHeader(channel, buffer);
	buffer->flip();
	char storageStatus = buffer->get();
	if (storageStatus != CLEAN_GENERATOR)
	{
		stringstream ss;
		ss << "Id file not properly shutdown [ " <<
			fileName->getFileName() << " ], delete this id file and build a new one";
		throw new runtime_error(ss.str());
	}
	long id = buffer->getLong();

	delete buffer;
	return id;
}

long IdContainer::readHighId(FileChannel * file)
{
	try
	{
		StoreChannel *channel = new StoreChannel(file->open("r"));
		long id = readAndValidate(channel, file);
		delete channel;
		return id;
	}
	catch (const runtime_error &e) {
		throw e;
	}
}

long IdContainer::readDefragCount(FileChannel * file)
{
	try
	{
		StoreChannel *channel = new StoreChannel(file->open("r"));
		OffsetChannel * offsetChannel = new OffsetChannel(channel, HEADER_SIZE);
		long count = FreeIdKeeper::countFreeIds(offsetChannel);
		delete offsetChannel;
		return count;
	}
	catch (const runtime_error &e) {
		throw e;
	}
}

long IdContainer::getReusableId()
{
	return freeIdKeeper->getId();
}

long * IdContainer::getReusableIds(const int & numberOfIds)
{
	return freeIdKeeper->getIds(numberOfIds);
}

IdRange * IdContainer::getReusableIdBatch(const int & maxSize)
{
	long * tmpIdArr = new long[maxSize];
	int count = 0;
	while (count < maxSize)
	{
		long id = freeIdKeeper->getId();
		if (id == NO_RESULT)
		{
			break;
		}
		tmpIdArr[count++] = id;
	}
	if (count != maxSize) 
	{
		tmpIdArr[count] = '\0';
	} 

	return new IdRange(tmpIdArr, 0, 0);
}

void IdContainer::freeId(const long & id)
{
	freeIdKeeper->freeId(id);
}

long IdContainer::getFreeIdCount()
{
	return freeIdKeeper->getCount();
}

void IdContainer::markAsSticky()
{
	ByteBuffer *buffer = new ByteBuffer()->allocate(sizeof(char));
	buffer->put(STICKY_GENERATOR)->flip();
	fileChannel->position(0);
	fileChannel->writeAll(buffer);
	fileChannel->flush();
	delete buffer;
}

void IdContainer::markAsCleanlyClosed()
{
	// remove sticky
	ByteBuffer * buffer = new ByteBuffer()->allocate(sizeof(char));
	buffer->put(CLEAN_GENERATOR)->flip();
	fileChannel->position(0);
	fileChannel->writeAll(buffer);
	delete buffer;
}

void IdContainer::close(const long & highId)
{
	if (!closed)
	{
		try
		{
			freeIdKeeper->close();
			writeHeader(highId);
			markAsCleanlyClosed();
			closeChannel();
		}
		catch (const runtime_error &e)
		{
			throw new runtime_error("Unable to close id file");
		}
	}
}

void IdContainer::closeChannel()
{
	fileChannel->flush();
	fileChannel->close();
	fileChannel = NULL;
	closed = true;
}

void IdContainer::writeHeader(const long & highId)
{
	ByteBuffer * buffer = new ByteBuffer()->allocate(HEADER_SIZE);
	buffer->put(STICKY_GENERATOR)->putLong(highId)->flip();
	fileChannel->position(0);
	fileChannel->writeAll(buffer);
	delete buffer;
}

void IdContainer::remove()
{
	if (!closed)
	{
		try
		{
			closeChannel();
		}
		catch (const runtime_error &e)
		{
			throw new runtime_error("Unable to close id file ");
		}
	}

	file->close();
}

void IdContainer::readHeader(StoreChannel * channel, ByteBuffer * buffer)
{
	try
	{
		channel->readAll(buffer);
	}
	catch (const runtime_error &e)
	{
		throw new runtime_error("Unable to read header, bytes read: ");
	}
}

char * IdContainer::getBufferBytes(ByteBuffer * buffer)
{
	char* bytes = new char[buffer->getPosition()];
	buffer->get(bytes);
	return bytes;
}
