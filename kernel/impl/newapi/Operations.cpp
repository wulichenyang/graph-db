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
	ktx->assertOpen();
	// statement ��� context ����ĳЩ״̬
	long nodeId = statement->reserveNode();
	ktx->getTxState()->nodeDoCreate(nodeId);
	return nodeId;
}

bool Operations::nodeDelete(long node)
{
	ktx->assertOpen();
	if (ktx->hasTxStateWithChanges())
	{
		// ���֮ǰ�в�������state�б仯�����StateTx�Ƿ��Ѿ�����˸õ㣬
		// ����ӣ�δ�ύ
		if (ktx->getTxState()->nodeIsAddedInThisTx(node))
		{
			// TxState.nodeDoDelete
			// ȥ������sets
			ktx->getTxState()->nodeDoDelete(node);
			return true;
		}
		// �� tx �Ѿ�ɾ���õ㣬�򷵻ش���
		if (ktx->getTxState()->nodeIsDeletedInThisTx(node))
		{
			// already deleted
			return false;
		}
	}

	// ��ȡ������
	// ktx.locks().optimistic().acquireExclusive(ktx.lockTracer(), ResourceTypes.NODE, node);
	// �����ж��Ƿ��Ѿ���store������node��ɾ���ýڵ�
	if (allStoreHolder->nodeExistsInStore(node))
	{
		// TxState.nodeDoDelete
		// ȥ������sets
		ktx->getTxState()->nodeDoDelete(node);
		return true;
	}

	// tried to delete node that does not exist
	return false;

}

long Operations::relationshipCreate(long sourceNode, int relationshipType, long targetNode)
{
	ktx->assertOpen();
	// ������� relType
	//sharedRelationshipTypeLock(relationshipType);
	// ������ Node
	//lockRelationshipNodes(sourceNode, targetNode);

	nodeExists(sourceNode);
	nodeExists(targetNode);

	long id = statement->reserveRelationship();
	ktx->getTxState()->relationshipDoCreate(id, relationshipType, sourceNode, targetNode);
	return id;
}

