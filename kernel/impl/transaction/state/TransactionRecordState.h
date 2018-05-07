#pragma once
#include <stdexcept>

using namespace std;
// 1������Nodes��Rels��txstate�ﱣ���״̬��Ϣ��ת����
// changeSet���record
// 2����changeSet���records��װ��Commands���֮�����д���ļ�
class TransactionRecordState
{
public:
	TransactionRecordState();
	~TransactionRecordState();

	void extractCommands(vector<Command> *commands);
	void nodeCreate(long nodeId);
	void nodeDelete(long nodeId);
	void relCreate(long id, int typeId, long startNodeId, long endNodeId);
	void relDelete(long relId);

private:
	NeoStores *neoStores;
	NodeStore *nodeStore;
	RelationshipStore *relationshipStore;
	RecordChangeSet *recordChangeSet;
	ResourceLocker *locks;
	RelationshipCreator *relationshipCreator;
	RelationshipDeleter *relationshipDeleter;

	RecordChanges<NeoStoreRecord> neoStoreRecord;
	bool prepared;

	vector<DynamicRecord> markNotInUse(vector<DynamicRecord> dynamicLabelRecords);
	void getAndDeletePropertyChain(NodeRecord *nodeRecord);
};

