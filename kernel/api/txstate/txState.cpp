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

bool TxState::ifHasChanges()
{
	return hasChanges;
}

void TxState::nodeDoDelete(long nodeId)
{
	nodes().remove(nodeId);
	if (!nodeStatesMap.isEmpty())
	{
		NodeState nodeState = nodeStatesMap.remove(nodeId);

		// NodeState.labelDiffSets()
		SuperDiffSets<int> diff = nodeState.getLabelDiffSets();
		set<int> added = diff.getAdded();

		set<int>::iterator it = added.begin();
		
		for (; it != added.end(); it++)
		{
			// 删除掉相关label id hash的map<Diffsets<nodeId>>里Diffsets里的相应nodeId
			getLabelStateNodeDiffSets(*it).remove(nodeId);
		}
		// 清除关于该点的Rel、Prop、
		nodeState.clear();
	}
	dataChanged();
	}
SuperDiffSets<int> TxState::getLabelStateNodeDiffSets(long nodeId)
{
	LabelState labelState = labelStatesMap.get(nodeId);
	return labelState.nodeDiffSets();
}

RemovalsCountingDiffSets TxState::nodes()
{
	return RemovalsCountingDiffSets();
}
