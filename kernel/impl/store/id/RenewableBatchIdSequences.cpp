#include "RenewableBatchIdSequences.h"




RenewableBatchIdSequences::RenewableBatchIdSequences()
{
}


RenewableBatchIdSequences::~RenewableBatchIdSequences()
{
	delete[]idGenerator;
}

RenewableBatchIdSequences::RenewableBatchIdSequences(NeoStores * stores, int batchSize)
{

}

long RenewableBatchIdSequences::nextId(StoreType type)
{
	return idGenerator(type)->nextId();
}

IdGenerator * RenewableBatchIdSequences::idGenerator(StoreType type)
{
	return types[type];
}

void RenewableBatchIdSequences::close()
{
}
