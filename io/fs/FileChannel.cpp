#include "FileChannel.h"



FileChannel::FileChannel()
{
	this->pFile = NULL;
	this->path = (char*)"";
	this->modeAttribute = (char*)"";
}


FileChannel::~FileChannel()
{
	delete[]path;
	delete[]modeAttribute;

	if (!(this->pFile == NULL))
	{
		fclose(this->pFile);
		delete[]pFile;
	}
}

FileChannel* FileChannel::open(char * path, char * mode)
{
	FILE *p = fopen( path, mode);
	this->path = (char*)path;
	this->modeAttribute = (char*)mode;
	try
	{
		if (p == NULL)
		{
			throw std::invalid_argument("Failed to open file.");
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
	}

	this->pFile = p;
	return this;
}

FILE * FileChannel::getFilePtr()
{
	return this->pFile;
}

int FileChannel::read(ByteBuffer * dst)
{	
	int leftSize = (dst->getCapacity() - dst->getPosition());

	if (leftSize >= BUF_SIZE) {
		int len = fread(dst + dst->getPosition(), 1, BUF_SIZE, this->getFilePtr());
		dst->nextReadBufSeq(len);
		return len;
	}
	else
	{
		int len = fread(dst + dst->getPosition(), 1, leftSize, this->getFilePtr());
		dst->nextReadBufSeq(len);
		return len;
	}

	//int readSize = size() - position();
	//dst->allocate(readSize);

	//int realReadSize = 0;

	//char buf[BUF_SIZE + 1];
	//memset(buf, '\0', sizeof(buf));
	//int len = 0;

	//while (!feof(this->getFilePtr())) {
	//	len = fread(buf, 1, BUF_SIZE, this->getFilePtr());
	//	// 不满buf_size的部分清除脏数据
	//	if (len != BUF_SIZE) {
	//		buf[len] = '\0';
	//	}

	//	realReadSize += len;
	//	dst->appendToBuf(buf);
	//}
	//return realReadSize;
}

long FileChannel::read(ByteBuffer ** dst, int offset, int length)
{
}

int FileChannel::read(ByteBuffer * dst, long position)
{
	this->position(position);

	int leftSize = (dst->getCapacity() - dst->getPosition());

	if (leftSize >= BUF_SIZE) {
		int len = fread(dst + dst->getPosition(), 1, BUF_SIZE, this->getFilePtr());
		dst->nextReadBufSeq(len);
		return len;
	}
	else
	{
		int len = fread(dst + dst->getPosition(), 1, leftSize, this->getFilePtr());
		dst->nextReadBufSeq(len);
		return len;
	}

	//int readSize = size() - this->position();
	//dst->allocate(readSize);
	//int realReadSize = 0;

	//char buf[BUF_SIZE + 1];
	//memset(buf, '\0', sizeof(buf));
	//int len = 0;
	//while (!feof(this->getFilePtr())) {
	//	len = fread(buf, 1, BUF_SIZE, this->getFilePtr());
	//	// 不满buf_size的部分清除脏数据
	//	if (len != BUF_SIZE) {
	//		buf[len] = '\0';
	//	}
	//	realReadSize += len;
	//	dst->appendToBuf(buf);
	//}
	//return realReadSize;
}

// overlap
int FileChannel::write(ByteBuffer * src)
{
	int realWriteSize;
	char *buf = src->nextWriteBufSeq(&realWriteSize);
	// write BUF_SIZE bytes per time
	return fwrite(buf, 1, realWriteSize, this->getFilePtr());

	//int size = src->getLimit() - src->getPosition();
	//int loop = (size / BUF_SIZE) + 1;
	//int leftBytes = size % BUF_SIZE;

	//int realWriteSize = 0;
	//int len = 0;

	//for (size_t i = 0; i < loop; i++) {

	//	if (i == loop - 1) {
	//		len = fwrite(src->readBuf(leftBytes), 1, leftBytes, this->getFilePtr());
	//		realWriteSize += len;
	//		break;
	//	}
	//	len = fwrite(src->readBuf(BUF_SIZE), 1, BUF_SIZE, this->getFilePtr());
	//	realWriteSize += len;
	//}

	//flush();

	//return realWriteSize;
}

long FileChannel::write(ByteBuffer ** src, int offset, int length)
{
	return 0;
}

int FileChannel::write(ByteBuffer * src, long newPosition)
{
	position(newPosition);

	int realWriteSize;
	char *buf = src->nextWriteBufSeq(&realWriteSize);
	// write BUF_SIZE bytes per time
	return fwrite(buf, 1, realWriteSize, this->getFilePtr());

	//position(newPosition);

	//int size = src->getLimit() - src->getPosition();
	//int loop = (size / BUF_SIZE) + 1;
	//int leftBytes = size % BUF_SIZE;

	//int realWriteSize = 0;
	//int len = 0;

	//for (size_t i = 0; i < loop; i++) {

	//	if (i == loop - 1) {
	//		len = fwrite(src->readBuf(leftBytes), 1, leftBytes, this->getFilePtr());
	//		realWriteSize += len;
	//		break;
	//	}
	//	len = fwrite(src->readBuf(BUF_SIZE), 1, BUF_SIZE, this->getFilePtr());
	//	realWriteSize += len;
	//}

	//flush();

	//return realWriteSize;
}

long FileChannel::position()
{
	return ftell(this->getFilePtr());
}

FileChannel * FileChannel::position(long newPosition)
{
	fseek(this->getFilePtr(), newPosition, SEEK_SET);
	return this;
}

long FileChannel::size()
{
	long position = this->position();
	fseek(this->getFilePtr(), 0L, SEEK_END);
	long size = ftell(this->getFilePtr());
	fseek(this->getFilePtr(), position, SEEK_SET);

	return size;
}

FileChannel * FileChannel::truncate(long size)
{
	return this;
}

void FileChannel::flush()
{
	fflush(this->getFilePtr());
}

FileLock * FileChannel::tryLock()
{
	return new FileLock();
}

void FileChannel::close()
{
}

bool FileChannel::isOpen()
{
	return this->ifOpen;
}

