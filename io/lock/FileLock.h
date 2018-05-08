#pragma once
#include <fcntl.h>
#include "../fs/FileChannel.h"

#define err_sys(info)                                                        \
        {                                                                    \
                fprintf(stderr, "%s:%s\n", info, strerror(errno));           \
                exit(EXIT_FAILURE);                                          \
        }

class FileLock
{
public:
	FileLock();
	~FileLock();

	// 非阻塞读写锁
	// 成功返回 0 ，失败（有其他锁）返回 -1；
	static int tryReadLock(FileChannel *fileChannel, off_t fileOffset, off_t len);
	static int tryWriteLock(FileChannel *fileChannel, off_t fileOffset, off_t len);
	static int unLock(FileChannel *fileChannel, off_t fileOffset, off_t len);

private:
	// F_UNLCK -> 0
	// F_WRLCK -> -1
	// F_RDLCK -> -2

	static int readLockReg(int fd, int type, off_t offset, int whence, off_t len);
	static int writeLockReg(int fd, int type, off_t offset, int whence, off_t len);
	static int unLockReg(int fd, int type, off_t offset, int whence, off_t len);


	static int readLock(int fd, off_t offset, int whence, off_t len);
	static int writeLock(int fd, off_t offset, int whence, off_t len);
	static int unLock(int fd, off_t offset, int whence, off_t len);

};

