#include "FileLock.h"



FileLock::FileLock()
{
}


FileLock::~FileLock()
{
}

int FileLock::tryReadLock(FileChannel * fileChannel, off_t fileOffset, off_t len)
{
	return readLock(fileChannel->getFilePtr, fileOffset, SEEK_SET, len);
}

int FileLock::tryWriteLock(FileChannel * fileChannel, off_t fileOffset, off_t len)
{
	return writeLock(fileChannel->getFilePtr, fileOffset, SEEK_SET, len);
}

int FileLock::unLock(FileChannel * fileChannel, off_t fileOffset, off_t len)
{
	unLock(fileChannel->getFilePtr, fileOffset, SEEK_SET, len);
}


int FileLock::readLockReg(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock, savelock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	savelock = lock;

	if (fcntl(fd, F_GETLK, &lock) < 0)
	{
		err_sys("fcntl error");
	}
	// 查看发现有写锁
	if (lock.l_type == F_WRLCK)
	{
		return -1;
	}
	// l_type == F_UNLCK, 没有写锁
	else
	{
		if(fcntl(fd, F_SETLK, &savelock) < 0)
			err_sys("fcntl error");
		return 0;
	}
}

int FileLock::writeLockReg(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock, savelock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	savelock = lock;

	if (fcntl(fd, F_GETLK, &lock) < 0)
	{
		err_sys("fcntl error");
	}
	// 查看发现有读/写锁
	if (lock.l_type == F_WRLCK || lock.l_type == F_RDLCK)
	{
		return -1;
	}
	// l_type == F_UNLCK, 没有读/写锁
	else
	{
		if (fcntl(fd, F_SETLK, &savelock) < 0)
			err_sys("fcntl error");
		return 0;
	}
}

int FileLock::unLockReg(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	if (fcntl(fd, F_SETLK, &lock) < 0)
	{
		err_sys("fcntl error");
	}
	return 0;
}

int FileLock::readLock(int fd, off_t offset, int whence, off_t len)
{
	return readLockReg(fd, F_RDLCK, offset, whence, len);
}

int FileLock::writeLock(int fd, off_t offset, int whence, off_t len)
{
	return writeLockReg(fd, F_WRLCK, offset, whence, len);
}

int FileLock::unLock(int fd, off_t offset, int whence, off_t len)
{
	return unLockReg(fd, F_UNLCK, offset, whence, len);
}
