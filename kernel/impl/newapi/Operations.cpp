#include "Operations.h"



Operations::Operations()
{
}

Operations::Operations(AllStoreHolder * allStoreHolder, StorageStatement * statement, KernelTransaction * ktx, KernelToken * token)
{
	this->allStoreHolder = allStoreHolder;
	this->statement = statement;
	this->ktx = ktx;
	this->token = token;
}


Operations::~Operations()
{
}

long Operations::nodeCreate()
{
	return 0;
}
