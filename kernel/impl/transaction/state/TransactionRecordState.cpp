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
		commands->push_back(new Command::LabelTokenCommand(*labelTokenIter->getBefore(), *labelTokenIter->forReadingLinkage()) );
	}

	// relationshipTypeTokenChanges
	vector<RecordChange<RelationshipTypeTokenRecord>*> RelationshipTypeTokenVec =
		recordChangeSet->getRelationshipTypeTokenChanges()->changes();
	vector<RecordChange<LabelTokenRecord>*>::iterator RelationshipTypeTokenIter =
		RelationshipTypeTokenVec.begin();

	for (; RelationshipTypeTokenIter != RelationshipTypeTokenVec.end(); RelationshipTypeTokenIter++)
	{
		commands->push_back(new Command::RelationshipTypeTokenCommand(*RelationshipTypeTokenIter->getBefore(), *RelationshipTypeTokenIter->forReadingLinkage()));
	}

	// Collect nodes
	vector<Command> nodeCommands;

	if (recordChangeSet->getNodeRecords()->changeSize() > 0)
	{
		// NodeRecordChanges
		vector<RecordChange<NodeRecord>*> NodeRecordVec =
			recordChangeSet->getNodeRecords()->changes();
		vector<RecordChange<NodeRecord>*>::iterator NodeRecordIter =
			NodeRecordVec.begin();

		for (; NodeRecordIter != NodeRecordVec.end(); NodeRecordIter++)
		{
			NodeRecord *record = prepared(*NodeRecordIter, nodeStore);
			integrityValidator.validateNodeRecord(record);
			nodeCommands.push_back(new Command::NodeCommand(*NodeRecordIter->getBefore(), record));
		}

		sortCommand(nodeCommands, COMMAND_SORTER);
	}

	// Collect Rels
	vector<Command> relCommands;

	if (recordChangeSet->getRelRecords()->changeSize() > 0)
	{
		// RelationshipRecordChanges
		vector<RecordChange<RelationshipRecord>*> relationshipRecordVec =
			recordChangeSet->getRelRecords()->changes();
		vector<RecordChange<RelationshipRecord>*>::iterator relationshipRecordIter =
			relationshipRecordVec.begin();

		for (; relationshipRecordIter != relationshipRecordVec.end(); relationshipRecordIter++)
		{
			RelationshipRecord *record = prepared(*relationshipRecordIter, relationshipStore);
			integrityValidator.validateRelationshipRecord(record);
			relCommands.push_back(new Command::RelationshipCommand(*relationshipRecordIter->getBefore(), record));
		}

		sortCommand(relCommands, COMMAND_SORTER);
	}
	// ����command�������push
	//   ���� propCommands, relCommands, relGroupCommands, nodeCommands
	//   �ĵ� propCommands, relCommands, relGroupCommands, nodeCommands
	//   ɾ�� propCommands, relCommands, relGroupCommands, nodeCommands
	addFiltered(commands, Command::Mode::CREATE, relCommands, nodeCommands);
	addFiltered(commands, Command::Mode::UPDATE, relCommands, nodeCommands);
	addFiltered(commands, Command::Mode::DELETE, relCommands, nodeCommands);

	prepared = true;
}

// ״̬ת��Ϊ�´�����Record������map��֮���������command
// relCreator/Deleter ����
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
	// Label��PropChain��������õ���Ϣ��
	// �õ��DynamicRecord ��Label id Arrayȫ�������nextLabel���
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
