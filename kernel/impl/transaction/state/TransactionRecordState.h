#pragma once
#include <stdexcept>

using namespace std;
// 1）接受Nodes和Rels在txstate里保存的状态信息，转化成
// changeSet里的record
// 2）将changeSet里的records封装到Commands里，供之后继续写入文件
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

