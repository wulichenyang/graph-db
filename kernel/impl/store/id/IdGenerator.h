#pragma once
#include "IdSequence.h"
#include "../../../../graphdb-api/Closeable.h"
class IdGenerator : public IdSequence, public Closeable
{
public:
	IdGenerator();
	~IdGenerator();

	virtual void setHighId(long id) = 0;
	virtual long getHighId() const = 0;
	virtual long getHighestPossibleIdInUse() const = 0;
	virtual void freeId(long id) = 0;
	virtual void close() = 0;
	virtual long getNumberOfIdsInUse() const = 0;
	virtual long getDefragCount() const = 0;
	virtual void remove() = 0;
};

