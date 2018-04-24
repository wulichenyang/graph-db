#include "IdGenerator.h"



IdGenerator::IdGenerator()
{
}

IdGenerator::IdGenerator(FileChannel * file, int grabSize, long max, bool aggressiveReuse, IdType idType, long highId)
{
	this->max = max;
	this->idType = idType;
	this->idContainer = new IdContainer(file, grabSize, aggressiveReuse);

	/*
	* The highId supplier will be called only if the id container tells us that the information found in the
	* id file is not reliable (typically the file had to be created)-> Calling the supplier can be a potentially
	* expensive operation->
	*/
	if (this->idContainer->init())
	{
		this->highId = idContainer->getInitialHighId();
	}
	else
	{
		this->highId = highId;
	}
}


IdGenerator::~IdGenerator()
{
	delete idContainer;
}

long IdGenerator::nextId()
{
	unique_lock<mutex> lock(nextIdMutex);

	assertStillOpen();
	long nextDefragId = idContainer->getReusableId();
	if (nextDefragId != IdContainer::NO_RESULT)
	{
		return nextDefragId;
	}

	if (highId == IdGenerator::INTEGER_MINUS_ONE)
	{
		highId++;
	}
	if (highId == IdGenerator::INTEGER_MINUS_ONE)
	{
		throw new runtime_error("ReservedIdException");
	}
	if (highId < 0) {
		throw new runtime_error("NegativeIdException");
	}
	if (highId > max)
	{
		throw new runtime_error("IdCapacityExceededException");
	}
	return highId++;
}

IdRange *IdGenerator::nextIdBatch(int size)
{
	unique_lock<mutex> lock(nextIdBatchMutex);

	assertStillOpen();
	long * reusableIds = idContainer->getReusableIds(size);
	int sizeLeftForRange = size - Computer::arrayLen(reusableIds);
	long start = highId;
	setHighId(start + sizeLeftForRange);
	return new IdRange(reusableIds, start, sizeLeftForRange);
}

void IdGenerator::setHighId(long id)
{
	unique_lock<mutex> lock(setHighIdMutex);

	if (id < 0) {
		throw new runtime_error("NegativeIdException");
	}
	if (id > max)
	{
		throw new runtime_error("IdCapacityExceededException");
	}
	highId = id;
}

long IdGenerator::getHighId()
{
	unique_lock<mutex> lock(getHighIdMutex);
	return highId;
}

long IdGenerator::getHighestPossibleIdInUse()
{
	unique_lock<mutex> lock(getHighestPossibleIdInUseMutex);
	return highId - 1;
}

void IdGenerator::freeId(long id)
{
	unique_lock<mutex> lock(freeIdMutex);
	idContainer->assertStillOpen();
	if (id == IdGenerator::INTEGER_MINUS_ONE)
	{
		return;
	}
	if (id < 0 || id >= highId)
	{
		throw new out_of_range("Illegal id[], highId is ");
	}
	idContainer->freeId(id);
}

void IdGenerator::close()
{
	unique_lock<mutex> lock(closeMutex);
	idContainer->close(highId);
}

void IdGenerator::createGenerator(FileChannel * file, long highId, bool throwIfFileExists)
{
	IdContainer::createEmptyIdFile(file, highId, throwIfFileExists);
}

long IdGenerator::readHighId(FileChannel * file)
{
	return IdContainer::readHighId(file);
}

long IdGenerator::readDefragCount(FileChannel * file)
{
	return IdContainer::readDefragCount(file);
}

long IdGenerator::getNumberOfIdsInUse()
{
	unique_lock<mutex> lock(getNumberOfIdsInUseMutex);
	return highId - getDefragCount();
}

long IdGenerator::getDefragCount()
{
	unique_lock<mutex> lock(getDefragCountMutex);
	return idContainer->getFreeIdCount();
}

void IdGenerator::remove()
{
	unique_lock<mutex> lock(removeMutex);
	idContainer->remove();
}

string IdGenerator::toString()
{
	return "IdGeneratorImpl ";
}

void IdGenerator::assertStillOpen()
{
	idContainer->assertStillOpen();
}
