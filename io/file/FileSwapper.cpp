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
inline long FileSwapper<RECORD>::read(RECORD * record)
{
	//try
	//{
	//	FileChannel *channel = channel(record->getId());
	//	long fileOffset = record->getId() * this->recordSize;
	//	return swapIn(record, fileOffset, channel);
	//}
	//catch (const std::exception& e)
	//{
	//	cerr << e.what();
	//}
}

template<class RECORD>
inline long FileSwapper<RECORD>::write(RECORD *record)
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
inline int FileSwapper<RECORD>::swapOut(RECORD * record, long fileOffset, FileChannel * fileChannel)
{
	// 循环尝试获取写锁直到没有读锁时成功上锁
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
