#pragma once
#include"../../../transaction/state/TransactionRecordState.h"
class TransactionToRecordStateVisitor
{
public:
	TransactionToRecordStateVisitor(TransactionRecordState *recordState);
	TransactionToRecordStateVisitor();
	~TransactionToRecordStateVisitor();
	void visitCreatedNode(long id);
	void visitDeletedNode(long id);
	void visitCreatedRelationship(long id, int type, long startNode, long endNode);
	void visitDeletedRelationship(long id);

private:
	TransactionRecordState *recordState;
};

