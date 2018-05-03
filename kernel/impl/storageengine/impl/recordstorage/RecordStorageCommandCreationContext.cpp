#include "RecordStorageCommandCreationContext.h"



RecordStorageCommandCreationContext::RecordStorageCommandCreationContext()
{
}


RecordStorageCommandCreationContext::~RecordStorageCommandCreationContext()
{
}

RecordStorageCommandCreationContext::RecordStorageCommandCreationContext(NeoStores * neoStores, int idBatchSize)
{
	this->neoStores = neoStores;
	this->idBatches = new RenewableBatchIdSequences(neoStores, idBatchSize);
}

long RecordStorageCommandCreationContext::nextId(StoreType storeType)
{
	return idBatches->nextId(storeType);
}

void RecordStorageCommandCreationContext::close()
{
	this->idBatches->close();
}
