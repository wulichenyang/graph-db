#pragma once
#include "../../../../graphdb-api/Closeable.h"
#include "../../../../primitive-collections/primitive/PrimitiveLongArrayQueue.h"
#include "../../../../io/fs/StoreChannel.h"
class FreeIdKeeper: public Closeable
{
public:
	FreeIdKeeper();
	~FreeIdKeeper();

private:
	const static int ID_ENTRY_SIZE = sizeof(long);
	PrimitiveLongArrayQueue freeIds = PrimitiveLongArrayQueue();
	PrimitiveLongArrayQueue readFromDisk = PrimitiveLongArrayQueue();
	StoreChannel channel;
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
	
};

