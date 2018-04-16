#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

class FileLock
{
public:
	FileLock() {
		fcntl()
	};
	~FileLock();
};

