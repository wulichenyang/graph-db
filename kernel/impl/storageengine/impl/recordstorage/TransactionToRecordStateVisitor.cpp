#include "TransactionToRecordStateVisitor.h"



TransactionToRecordStateVisitor::TransactionToRecordStateVisitor(TransactionRecordState * recordState)
{
	this->recordState = recordState;
}

TransactionToRecordStateVisitor::TransactionToRecordStateVisitor()
{
}


TransactionToRecordStateVisitor::~TransactionToRecordStateVisitor()
{
}

void TransactionToRecordStateVisitor::visitCreatedNode(long id)
{
	recordState->nodeCreate(id);
}

void TransactionToRecordStateVisitor::visitDeletedNode(long id)
{
	recordState->nodeDelete(id);
}

void TransactionToRecordStateVisitor::visitCreatedRelationship(long id, int type, long startNode, long endNode)
{
	recordState->relCreate(id, type, startNode, endNode);
}

void TransactionToRecordStateVisitor::visitDeletedRelationship(long id)
{
	recordState->relDelete(id);
}
