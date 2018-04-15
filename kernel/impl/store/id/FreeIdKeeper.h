#pragma once
#include "../../../../graphdb-api/Closeable.h"
#include "../../../../primitive-collections/primitive/PrimitiveLongArrayQueue.h"
class FreeIdKeeper: public Closeable
{
public:
	FreeIdKeeper();
	~FreeIdKeeper();

private:
	const static int ID_ENTRY_SIZE = sizeof(long);
	PrimitiveLongArrayQueue pp = PrimitiveLongArrayQueue();
};

