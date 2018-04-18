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
	}
}

FileChannel FileChannel::open(char * path, char * mode)
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
	return *this;
}

FILE * FileChannel::getFilePtr()
{
	return this->pFile;
}

int FileChannel::read(ByteBuffer * dst)
{	
	int readSize = size() - position();
	dst->allocate(readSize);

	char buf[BUF_SIZE + 1];
	memset(buf, '\0', sizeof(buf));

	while (!feof(this->getFilePtr())) {
		int len = fread(buf, 1, BUF_SIZE, this->getFilePtr());
		// 不满buf_size的部分清除脏数据
		if (len != BUF_SIZE) {
			buf[len] = '\0';
		}
		dst->appendToBuf(buf);
	}
	return readSize;
}

long FileChannel::read(ByteBuffer ** dst, int offset, int length)
{
}

int FileChannel::read(ByteBuffer * dst, long position)
{
	int readSize = size() - position;
	dst->allocate(readSize);

	char buf[BUF_SIZE + 1];
	memset(buf, '\0', sizeof(buf));

	while (!feof(this->getFilePtr())) {
		int len = fread(buf, 1, BUF_SIZE, this->getFilePtr());
		// 不满buf_size的部分清除脏数据
		if (len != BUF_SIZE) {
			buf[len] = '\0';
		}
		dst->appendToBuf(buf);
	}
	return readSize;
}

// overlap
int FileChannel::write(ByteBuffer * src)
{
	int size = src->getCapacity();
	int loop = (size / BUF_SIZE) + 1;
	int leftBytes = size % BUF_SIZE;

	for (size_t i = 0; i < loop; i++) {

		if (i == loop - 1) {
			fwrite(src->getBuf() + BUF_SIZE * i, 1, leftBytes, this->getFilePtr());
			break;
		}
		fwrite(src->getBuf() + BUF_SIZE * i, 1, BUF_SIZE, this->getFilePtr());
	}

	flush();

	return size;
}

long FileChannel::write(ByteBuffer ** src, int offset, int length)
{
	return 0;
}

int FileChannel::write(ByteBuffer * src, long newPosition)
{

	position(newPosition);

	int size = src->getCapacity();
	int loop = (size / BUF_SIZE) + 1;
	int leftBytes = size % BUF_SIZE;

	for (size_t i = 0; i < loop; i++) {

		if (i == loop - 1) {
			fwrite(src->getBuf() + BUF_SIZE * i, 1, leftBytes, this->getFilePtr());
			break;
		}
		fwrite(src->getBuf() + BUF_SIZE * i, 1, BUF_SIZE, this->getFilePtr());
	}

	flush();

	return size;
}

long FileChannel::position()
{
	return ftell(this->getFilePtr());
}

FileChannel FileChannel::position(long newPosition)
{
	fseek(this->getFilePtr(), newPosition, SEEK_SET);
	return *this;
}

long FileChannel::size()
{
	long position = this->position();
	fseek(this->getFilePtr(), 0L, SEEK_END);
	long size = ftell(this->getFilePtr());
	fseek(this->getFilePtr(), position, SEEK_SET);

	return size;
}

FileChannel FileChannel::truncate(long size)
{
	return FileChannel();
}

void FileChannel::flush()
{
	fflush(this->getFilePtr());
}

FileLock FileChannel::tryLock()
{
	return FileLock();
}

void FileChannel::close()
{
}

bool FileChannel::isOpen()
{
	return this->ifOpen;
}

