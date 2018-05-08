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
	// ѭ�����Ի�ȡд��ֱ��û�ж���ʱ�ɹ�����
	while (1)
	{
		if (FileLock::tryWriteLock(fileChannel, fileOffset, this->recordSize) == 0)
			break;
	}

	// д��buffer
	ByteBuffer *buf = new ByteBuffer();
	this->recordFormat->write(record, buf, this->recordSize);

	// ��bufferд�����
	int writeBytes = fileChannel->write(buf, fileOffset);
	// ˢ��
	fileChannel->flush();
	delete buf;
	// ��ȡ���⿪д��
	FileLock::unLock(fileChannel, fileOffset, this->recordSize);
	return writeBytes;
}
