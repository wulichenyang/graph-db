#include "FileSwapper.h"


template<class RECORD>
FileSwapper<RECORD>::FileSwapper()
{
}

template<class RECORD>
FileSwapper<RECORD>::~FileSwapper()
{
}

template<class RECORD>
long FileSwapper<RECORD>::read(RECORD * record, long id)
{
	try
	{
		FileChannel *channel = channel(id);
		long fileoffset = id * this->recordsize;
		return swapIn(record, fileoffset, channel);
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}
}

template<class RECORD>
long FileSwapper<RECORD>::write(RECORD *record)
{
	try
	{
		FileChannel *channel = channel(record->getId());
		long fileOffset = record->getId() * this->recordSize;
		return swapOut(record, fileOffset, channel);
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}
}

template<class RECORD>
int FileSwapper<RECORD>::swapIn(RECORD * record, long fileOffset, FileChannel * fileChannel)
{
	// 循环尝试获取读锁直到没有写锁时成功上锁
	while (1)
	{
		if (FileLock::tryReadLock(fileChannel, fileOffset, this->recordSize) == 0)
			break;
	}

	// 读磁盘到buffer
	ByteBuffer *buf = new ByteBuffer();
	buf->allocate(this->recordSize);

	int readBytes = fileChannel->read(buf, fileOffset);

	// buffer指针还原
	buf->flip();
	// 将buffer内容写入record
	this->recordFormat->read(record, buf, this->recordSize);

	delete buf;

	// 读完解开读锁
	FileLock::unLock(fileChannel, fileOffset, this->recordSize);
	return readBytes;
}

template<class RECORD>
int FileSwapper<RECORD>::swapOut(RECORD * record, long fileOffset, FileChannel * fileChannel)
{
	// 循环尝试获取写锁直到没有读/写锁时成功上锁
	while (1)
	{
		if (FileLock::tryWriteLock(fileChannel, fileOffset, this->recordSize) == 0)
			break;
	}

	// 写入buffer
	ByteBuffer *buf = new ByteBuffer();
	this->recordFormat->write(record, buf, this->recordSize);

	// 将buffer写入磁盘
	int writeBytes = fileChannel->write(buf, fileOffset);
	// 刷新
	fileChannel->flush();
	delete buf;
	// 读取完后解开写锁
	FileLock::unLock(fileChannel, fileOffset, this->recordSize);
	return writeBytes;
}
