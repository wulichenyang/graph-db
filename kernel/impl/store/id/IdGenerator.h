#pragma once
#include "IdSequence.h"
#include "../../../../graphdb-api/Closeable.h"
#include "IdContainer.h"
#include "IdType.h"
#include "../../util/function/LongSupplier.h"
#include <mutex>
#include "../../util/Computer.h"

class IdGenerator : public IdSequence, public Closeable
{
public:
	const static long INTEGER_MINUS_ONE = 0xFFFFFFFFL;

	IdGenerator();
	IdGenerator(FileChannel	*file , int grabSize, long max, bool aggressiveReuse,
		IdType idType, LongSupplier *highId);
	~IdGenerator();

	long nextId();
	IdRange *nextIdBatch(int size);
	void setHighId(long id);
	long getHighId();
	long getHighestPossibleIdInUse();
	void freeId(long id);
	void close();
	static void createGenerator(FileChannel	*file, long highId,
	bool throwIfFileExists);
	static long readHighId(FileChannel	*file);
	static long readDefragCount(FileChannel	*file);
	long getNumberOfIdsInUse();
	long getDefragCount();
	void remove();
	string toString();
private:
	long max;
	IdContainer *idContainer;
	long highId;
	IdType idType;

	mutex nextIdMutex;
	mutex nextIdBatchMutex;
	mutex setHighIdMutex;
	mutex getHighIdMutex;
	mutex getHighestPossibleIdInUseMutex;
	mutex freeIdMutex;
	mutex closeMutex;
	mutex getNumberOfIdsInUseMutex;
	mutex getDefragCountMutex;
	mutex removeMutex;

	void assertStillOpen();

};

