#include "TransactionRecordState.h"



TransactionRecordState::TransactionRecordState()
{
}


TransactionRecordState::~TransactionRecordState()
{
}

void TransactionRecordState::extractCommands(vector<Command>* commands)
{
	// labelTokenChanges
	vector<RecordChange<LabelTokenRecord>*> labelTokenVec =
		recordChangeSet->getLabelTokenChanges()->changes();
	vector<RecordChange<LabelTokenRecord>*>::iterator labelTokenIter = 
		labelTokenVec.begin();
	for (; labelTokenIter != labelTokenVec.end(); labelTokenIter++)
	{
		commands->insert(new Command::LabelTokenCommand(*labelTokenIter->getBefore(), *labelTokenIter->forReadingLinkage()) );
	}

	// relationshipTypeTokenChanges
	vector<RecordChange<RelationshipTypeTokenRecord>*> RelationshipTypeTokenVec =
		recordChangeSet->getRelationshipTypeTokenChanges()->changes();
	vector<RecordChange<LabelTokenRecord>*>::iterator RelationshipTypeTokenIter =
		RelationshipTypeTokenVec.begin();
	for (; RelationshipTypeTokenIter != RelationshipTypeTokenVec.end(); RelationshipTypeTokenIter++)
	{
		commands->insert(new Command::RelationshipTypeTokenCommand(*RelationshipTypeTokenIter->getBefore(), *RelationshipTypeTokenIter->forReadingLinkage()));
	}

}

void TransactionRecordState::nodeCreate(long nodeId)
{
	NodeRecord *nodeRecord = recordChangeSet->getNodeRecords()->create(nodeId)->forChangingData();
	nodeRecord->setInUse(true);
	nodeRecord->setCreated();
}

void TransactionRecordState::nodeDelete(long nodeId)
{
	NodeRecord *nodeRecord = recordChangeSet->getNodeRecords()->getOrLoad(nodeId)->forChangingData();
	if (!nodeRecord->inUse())
	{
		throw new runtime_error("Unable to delete Node[] since it has already been deleted.");
	}
	nodeRecord->setInUse(false);
	// Label和PropChain清除（仅该点信息）
	// 该点的DynamicRecord 即Label id Array全部清除，nextLabel清除
	nodeRecord->setLabelField((Record(Record::NO_LABELS_FIELD)).intValue(),
		markNotInUse(nodeRecord->getDynamicLabelRecords()));
	getAndDeletePropertyChain(nodeRecord);
}

void TransactionRecordState::relCreate(long id, int typeId, long startNodeId, long endNodeId)
{
	relationshipCreator->relationshipCreate(id, typeId, startNodeId, endNodeId, recordChangeSet, locks);
}

void TransactionRecordState::relDelete(long relId)
{
	relationshipDeleter->relDelete(relId, recordChangeSet, locks);
}
