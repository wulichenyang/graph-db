#pragma once
#include "../../../../graphdb-api/Closeable.h"
class FreeIdKeeper: public Closeable
{
public:
	FreeIdKeeper();
	~FreeIdKeeper();
};

