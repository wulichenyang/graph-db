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
	if (!hasAddedRelationships())
	{
		relationshipsAdded = RelationshipChangesForNode(state);
	}
	relationshipsAdded.addRelationship(relId, typeId, direction);
}

void NodeState::removeRelationship(long relId, int typeId, Direction direction)
{
	if (hasAddedRelationships())
	{
		if (relationshipsAdded.removeRelationship(relId, typeId, direction))
		{
			return;
		}
	}
	if (!hasRemovedRelationships())
	{
		relationshipsRemoved = RelationshipChangesForNode(state);
	}
	relationshipsRemoved.addRelationship(relId, typeId, direction);
}

void NodeState::clear()
{
	if (hasAddedRelationships())
	{
		relationshipsAdded.clear();
	}
	if (hasRemovedRelationships())
	{
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

set<long> NodeState::getAddedRelationships(Direction direction)
{
	return hasAddedRelationships() ? relationshipsAdded.getRelationships(direction):
		 set<long>();
}

set<long> NodeState::getAddedRelationships(Direction direction, int * relTypes)
{
	return hasAddedRelationships() ? relationshipsAdded.getRelationships(direction, relTypes) :
		set<long>();
}

set<long> NodeState::getAddedRelationships()
{
	return hasAddedRelationships() ? relationshipsAdded.getRelationships() :
		set<long>();
}

set<long>* NodeState::getAddedRelationships(RelationshipDirection direction, int relType)
{
	return hasAddedRelationships() ? relationshipsAdded.getRelationships(direction, relType) :
		new set<long>();
}
