#include "AllStoreHolder.h"



AllStoreHolder::AllStoreHolder()
{
}

AllStoreHolder::AllStoreHolder(StorageEngine * engine, StorageStatement * statement, KernelTransaction * ktx)
	:Read(ktx)
{
	this->storeReadLayer = engine->storeReadLayer();
	this->statement = statement;
}


AllStoreHolder::~AllStoreHolder()
{
}

bool AllStoreHolder::nodeExistsInStore(long id)
{
	return storeReadLayer->nodeExists(id);
}
