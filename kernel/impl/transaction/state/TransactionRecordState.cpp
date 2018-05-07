#include "TransactionRecordState.h"



TransactionRecordState::TransactionRecordState()
{
}


TransactionRecordState::~TransactionRecordState()
{
}

void TransactionRecordState::nodeCreate(long nodeId)
{
	NodeRecord *nodeRecord = recordChangeSet->getNodeRecords().create(nodeId, null).forChangingData();
	nodeRecord->setInUse(true);
	nodeRecord->setCreated();
}

void TransactionRecordState::nodeDelete(long nodeId)
{
}

void TransactionRecordState::relCreate(long id, int typeId, long startNodeId, long endNodeId)
{
}

void TransactionRecordState::relDelete(long relId)
{
}
