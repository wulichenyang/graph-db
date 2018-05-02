#pragma once
#include "Read.h"

class AllStoreHolder: public Read
{
public:
	AllStoreHolder();
	AllStoreHolder(StorageEngine *engine,
		StorageStatement *statement,
		KernelTransaction *ktx);
	~AllStoreHolder();

private:
	StorageStatement *statement;
	StoreReadLayer *storeReadLayer;
};

