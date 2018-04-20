#pragma once
#include "IdRange.h"
#include <stdexcept>
#include "../../../../io/fs/FileChannel.h"
#include "../../../../io/fs/StoreChannel.h"
#include "FreeIdKeeper.h"
#include "../../../../io/fs/OffsetChannel.h"
#include <stdexcept>
#include <string>

using namespace std;

class IdContainer
{
public:
	const static long NO_RESULT = -1;
	// header format: sticky(byte), nextFreeId(long)
	const static int HEADER_SIZE = sizeof(char) + sizeof(long);
	IdContainer();
	IdContainer(FileChannel * file, int grabSize, bool aggressiveReuse);
	~IdContainer();
	/**
	* Initializes the id generator and performs a simple validation. Returns true if the initialization restored
	* properly on disk state, false otherwise (such as creating an id file from scratch).
	* Will throw {@link InvalidIdGeneratorException} if the id file is found to be damaged or unclean.
	*/
	// @return false 文件不存在 新建文件
	// @return true 存在则打开文件
	bool init();
	bool isClosed();
	long getInitialHighId();
	void assertStillOpen();
	// 读取文件中的 highId
	long readAndValidateHeader();
	static long readAndValidate(StoreChannel *channel, FileChannel *fileName);
	static long readHighId(FileChannel *file);
	// 文件中 freeId 个数
	static long readDefragCount(FileChannel *file);
	/**
	* @return next free id or {@link IdContainer#NO_RESULT} if not available
	*/
	long getReusableId();
	long * getReusableIds(const int &numberOfIds);
	IdRange *getReusableIdBatch(const int &maxSize);
	void freeId(const long &id);
	long getFreeIdCount();
	static void createEmptyIdFile(FileChannel *file, const long &highId, const bool &throwIfFileExists);
	string toString();

private:
	// if sticky the id generator wasn't closed properly so it has to be
	// rebuilt (go through the node, relationship, property, rel type etc files)
	const static char CLEAN_GENERATOR = (char)0;
	const static char STICKY_GENERATOR = (char)1;

	FileChannel *file;
	StoreChannel *fileChannel;
	bool closed = true;
	int grabSize;
	bool aggressiveReuse;
	FreeIdKeeper *freeIdKeeper;

	long initialHighId;

	void markAsSticky();
	void markAsCleanlyClosed();
	void close(const long &highId);
	void closeChannel();
	void writeHeader(const long &highId);
	void remove();
	static void readHeader(StoreChannel *channel, ByteBuffer *buffer);
	static char* getBufferBytes(ByteBuffer *buffer);
};

