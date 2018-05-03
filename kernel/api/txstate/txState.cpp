#include "TxState.h"

LabelState TxState::LABEL_STATE = LabelState();
NodeState  TxState::NODE_STATE = NodeState();
RelationshipState  TxState::RELATIONSHIP_STATE = RelationshipState();

TxState::TxState()
{
}


TxState::~TxState()
{
}

void TxState::nodeDoCreate(long nodeId)
{
	nodes().add(nodeId);
	dataChanged();
}

void TxState::changed()
{
	this->hasChanges = true;
}

void TxState::dataChanged()
{
	changed();
	this->hasDataChanges = true;
}

RemovalsCountingDiffSets TxState::nodes()
{
	return RemovalsCountingDiffSets();
}
