#include "NodeState.h"


NodeState::NodeState()
{
}


NodeState::~NodeState()
{
}

NodeState::NodeState(long id, TxState *state) 
	:PropertyContainerState(id)
{
	this->state = state;
}

void NodeState::addRelationship(long relId, int typeId, Direction direction)
{
}

void NodeState::removeRelationship(long relId, int typeId, Direction direction)
{
}

void NodeState::clear()
{
	if (hasAddedRelationships())
	{
		// RelationshipChangesForNode
		relationshipsAdded.clear();
	}
	if (hasRemovedRelationships())
	{
		// RelationshipChangesForNode
		relationshipsRemoved.clear();
	}
}

bool NodeState::hasAddedRelationships()
{
	return relationshipsAdded.getTotalOutgoing() ||
		relationshipsAdded.getTotalIncoming() ||
		relationshipsAdded.getTotalLoops();
}

bool NodeState::hasRemovedRelationships()
{
	return relationshipsRemoved.getTotalIncoming ||
		relationshipsRemoved.getTotalIncoming ||
		relationshipsRemoved.getTotalLoops;
}

bool NodeState::hasRelationshipChanges()
{
	return hasAddedRelationships() || hasRemovedRelationships();
}

set<long> *NodeState::getAddedRelationships(Direction direction)
{
	return hasAddedRelationships() ? relationshipsAdded.getRelationships(direction) : 
		new set<long>();
}

set<long> *NodeState::getAddedRelationships(Direction direction, int * relTypes)
{
	return new set<long>();
}

set<long> *NodeState::getAddedRelationships()
{
	return new set<long>();
}

set<long> *NodeState::getAddedRelationships(RelationshipDirection direction, int relType)
{
	return new set<long>();
}
