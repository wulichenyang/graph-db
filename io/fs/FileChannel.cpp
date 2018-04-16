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
	FILE *p;
	fopen_s(&p, path, mode);
	this->path = (char*)path;
	this->modeAttribute = (char*)mode;
	try
	{
		if (p == NULL)
		{
			throw std::invalid_argument("Failed to open file.");
		}
	}
	catch (const std::exception& e)
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

	char buf[BUF_SIZE];
	while (!feof(this->getFilePtr())) {
		fread(buf, 1, BUF_SIZE, this->getFilePtr());
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

	char buf[BUF_SIZE];
	while (!feof(this->getFilePtr())) {
		fread(buf, 1, BUF_SIZE, this->getFilePtr());
		dst->appendToBuf(buf);
	}
	return readSize;
}

int FileChannel::write(ByteBuffer * src)
{
	return 0;
}

long FileChannel::write(ByteBuffer ** src, int offset, int length)
{
	return 0;
}

int FileChannel::write(ByteBuffer * src, long position)
{
	return 0;
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
	return false;
}

