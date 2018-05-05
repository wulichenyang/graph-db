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
	getNodes().add(nodeId);
	dataChanged();
}

RemovalsCountingDiffSets TxState::getRelationships()
{
	return this->relationships;
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
	getNodes().remove(nodeId);
	if (!nodeStatesMap.isEmpty())
	{
		NodeState *nodeState = nodeStatesMap.remove(nodeId);

		// NodeState.labelDiffSets()
		SuperDiffSets<int> diff = nodeState->getLabelDiffSets();
		set<int> added = diff.getAdded();

		set<int>::iterator it = added.begin();
		
		for (; it != added.end(); it++)
		{
			// 删除掉相关label id hash的map<Diffsets<nodeId>>里Diffsets里的相应nodeId
			getLabelStateNodeDiffSets(*it).remove(nodeId);
		}
		// 清除关于该点的Rel、Prop、
		nodeState->clear();
	}
	dataChanged();
}

SuperDiffSets<int> TxState::getLabelStateNodeDiffSets(long nodeId)
{
	LabelState *labelState = labelStatesMap.get(nodeId);
	return labelState->nodeDiffSets();
}

bool TxState::nodeIsDeletedInThisTx(long nodeId )
{
	return nodes.wasRemoved(nodeId);
}

bool TxState::nodeIsAddedInThisTx(long nodeId)
{
	return  nodes.isAdded(nodeId);
}

void TxState::relationshipDoCreate(long id, int relationshipTypeId, long startNodeId, long endNodeId)
{
	getRelationships().add(id);

	if (startNodeId == endNodeId)
	{
		getOrCreateNodeState(startNodeId)->addRelationship(id, relationshipTypeId, Direction::BOTH);
	}

	else
	{
		// NodeState 保存着该 node 的添加、删除的RelSets
		getOrCreateNodeState(startNodeId)->addRelationship(id, relationshipTypeId, Direction::OUTGOING);
		getOrCreateNodeState(endNodeId)->addRelationship(id, relationshipTypeId, Direction::INCOMING);
	}

	getOrCreateRelationshipState(id)->setMetaData(startNodeId, endNodeId, relationshipTypeId);

	dataChanged();
}

void TxState::relationshipDoDelete(long id, int type, long startNodeId, long endNodeId)
{
	getRelationships().remove(id);

	if (startNodeId == endNodeId)
	{
		getOrCreateNodeState(startNodeId)->removeRelationship(id, type, Direction::BOTH);
	}

	else
	{
		// NodeStateImpl 保存着该 node 的添加、删除的RelSets            
		getOrCreateNodeState(startNodeId)->removeRelationship(id, type, Direction::OUTGOING);
		getOrCreateNodeState(endNodeId)->removeRelationship(id, type, Direction::INCOMING);
	}

	if (!relationshipStatesMap.isEmpty())
	{
		RelationshipState *removed = relationshipStatesMap.remove(id);
		// RelationshipStateImpl ---|> PropertyContainerStateImpl.clear删除属性
		removed->clear();
	}

	dataChanged();
}

NodeState *TxState::getOrCreateNodeState(long nodeId)
{
	return nodeStatesMap.getOrCreate(nodeId);
}

RelationshipState *TxState::getOrCreateRelationshipState(long relationshipId)
{
	return relationshipStatesMap.getOrCreate(relationshipId);
}

RemovalsCountingDiffSets TxState::getNodes()
{
	return this->nodes;
}
