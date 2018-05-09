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
	// ѭ�����Ի�ȡ����ֱ��û��д��ʱ�ɹ�����
	while (1)
	{
		if (FileLock::tryReadLock(fileChannel, fileOffset, this->recordSize) == 0)
			break;
	}

	// �����̵�buffer
	ByteBuffer *buf = new ByteBuffer();
	buf->allocate(this->recordSize);

	int readBytes = fileChannel->read(buf, fileOffset);

	// bufferָ�뻹ԭ
	buf->flip();
	// ��buffer����д��record
	this->recordFormat->read(record, buf, this->recordSize);

	delete buf;

	// ����⿪����
	FileLock::unLock(fileChannel, fileOffset, this->recordSize);
	return readBytes;
}

template<class RECORD>
int FileSwapper<RECORD>::swapOut(RECORD * record, long fileOffset, FileChannel * fileChannel)
{
	// ѭ�����Ի�ȡд��ֱ��û�ж�/д��ʱ�ɹ�����
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
