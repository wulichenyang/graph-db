#include "GraphDatabaseFacade.h"



GraphDatabaseFacade::GraphDatabaseFacade()
{
}


GraphDatabaseFacade::~GraphDatabaseFacade()
{
	delete this->tx;
}

NodeProxy *GraphDatabaseFacade::createNode()
{
	return new NodeProxy();
}

KernelTransaction *GraphDatabaseFacade::beginTx()
{
	this->tx = new KernelTransaction();
	return this->tx;
}

KernelTransaction * GraphDatabaseFacade::getTx()
{
	return this->tx;
}
