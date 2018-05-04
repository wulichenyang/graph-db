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
	// statement 里的 context 管理某些状态
	long nodeId = statement->reserveNode();
	ktx->getTxState()->nodeDoCreate(nodeId);
	return nodeId;
}

bool Operations::nodeDelete(long node)
{
	ktx->assertOpen();
	if (ktx->hasTxStateWithChanges())
	{
		// 如果之前有操作过，state有变化，检测StateTx是否已经添加了该点，
		// 已添加，未提交
		if (ktx->getTxState()->nodeIsAddedInThisTx(node))
		{
			// TxState.nodeDoDelete
			// 去掉缓冲sets
			ktx->getTxState()->nodeDoDelete(node);
			return true;
		}
		// 该 tx 已经删除该点，则返回错误
		if (ktx->getTxState()->nodeIsDeletedInThisTx(node))
		{
			// already deleted
			return false;
		}
	}

	// 获取排它锁
	// ktx.locks().optimistic().acquireExclusive(ktx.lockTracer(), ResourceTypes.NODE, node);
	// 否则判断是否已经在store里面有node，删除该节点
	if (allStoreHolder->nodeExistsInStore(node))
	{
		// TxState.nodeDoDelete
		// 去掉缓冲sets
		ktx->getTxState()->nodeDoDelete(node);
		return true;
	}

	// tried to delete node that does not exist
	return false;

}

long Operations::relationshipCreate(long sourceNode, int relationshipType, long targetNode)
{
	ktx->assertOpen();
	// 共享读锁 relType
	//sharedRelationshipTypeLock(relationshipType);
	// 排他锁 Node
	//lockRelationshipNodes(sourceNode, targetNode);

	nodeExists(sourceNode);
	nodeExists(targetNode);

	long id = statement->reserveRelationship();
	ktx->getTxState()->relationshipDoCreate(id, relationshipType, sourceNode, targetNode);
	return id;
}

