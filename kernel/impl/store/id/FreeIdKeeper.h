#pragma once
#include "../../../../graphdb-api/Closeable.h"
#include "../../../../primitive-collections/primitive/PrimitiveLongArrayQueue.h"
#include "../../../../io/fs/StoreChannel.h"
#include "IdContainer.h"
#include <math.h>
#include <stdexcept>
#include <assert.h>
class FreeIdKeeper: public Closeable
{
public:
	FreeIdKeeper();
	~FreeIdKeeper();
	FreeIdKeeper(StoreChannel *channel, int batchSize, bool aggressiveMode);
	static long countFreeIds(StoreChannel *channel);
	// id -> freeIds, if len > batchSize ,  freeIds -> buf -> disk
	void freeId(long id);
	void truncate(long position);
	// if(freeId) id <- freeIds,  else id <- readFromDisk, else readFromDisk <- Disk
	long getId();
	// n 个 ids from freeIds and readFromDisk，不够就只读取磁盘总的freeIdCount个 to readFromDisk（还需要后续获得自增highId）
	long * getIds(int numberOfIds);

	long getCount();

	/*
	* Writes both freeIds and readFromDisk lists to disk and truncates the channel to size.
	* It forces but does not close the channel.
	*/
	// freeId -> disk; readFromDisk -> freeIds -> disk
	void close();
private:

	const static int ID_ENTRY_SIZE = sizeof(long);
	PrimitiveLongArrayQueue *freeIds = new PrimitiveLongArrayQueue();
	PrimitiveLongArrayQueue *readFromDisk = new PrimitiveLongArrayQueue();
	StoreChannel *channel;
	int batchSize;
	bool aggressiveMode;

	long freeIdCount;

	/**
	* Keeps the position where batches of IDs will be flushed out to.
	* This can be viewed as being put on top of a stack.
	*/
	long stackPosition;
	/**
	* The position before we started this run.
	* <p>
	* Useful to keep track of the gap that will form in non-aggressive mode
	* when IDs from old runs get reused and newly freed IDs are put on top
	* of the stack. During a clean shutdown the gap will be compacted away.
	* <p>
	* During an aggressive run a gap is never formed since batches of free
	* IDs are flushed on top of the stack (end of file) and also read in
	* from the top of the stack.
	*/
	long initialPosition;
	
	// IdFromDisk 缓冲区出队，不够直接从磁盘读取 batchSize 个id
	// 磁盘没有 freeId 则返回 NO_RESULT
	long getIdFromDisk();

	/*
	* After this method returns, if there were any entries found, they are placed in the readFromDisk list.
	*/
	// 从磁盘读 <= batchSize 个 id
	void readIdBatch();
	void readIdBatch0();

	/**
	* Flushes the currently collected in-memory freed IDs to the storage.
	*/
	// freeIds 超过 batchSize 则写入文件
	long flushFreeIds(ByteBuffer *writeBuffer);
	long flushFreeIds0(ByteBuffer *writeBuffer);
	/**
	* Compacts away the gap which will form in non-aggressive (regular) mode
	* when batches are read in from disk.
	* <p>
	* The gap will contain already used IDs so it is important to remove it
	* on a clean shutdown. The freed IDs will not be reused after an
	* unclean shutdown, as guaranteed by the external user.
	* <pre>
	* Below diagram tries to explain the situation
	*
	*   S = old IDs which are still free (on the Stack)
	*   G = the Gap which has formed, due to consuming old IDs
	*   N = the New IDs which have been freed during this run (will be compacted to the left)
	*
	*     stackPosition
	*          v
	* [ S S S S G G G N N N N N N N N ]
	*                ^
	*          initialPosition
	* </pre>
	* After compaction the state will be:
	* <pre>
	* [ S S S S N N N N N N N N ]
	* </pre>
	* and the last part of the file is truncated.
	*/
	void compact(ByteBuffer *writeBuffer);

};

