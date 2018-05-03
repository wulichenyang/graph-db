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
	KernelTransaction *transaction = getTx();
	return newNodeProxy(transaction->dataWrite()->nodeCreate());
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

NodeProxy * GraphDatabaseFacade::newNodeProxy(long nodeId)
{
	return new NodeProxy(this, nodeId);
}
