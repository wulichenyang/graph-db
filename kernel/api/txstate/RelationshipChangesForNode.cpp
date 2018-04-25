#include "RelationshipChangesForNode.h"



RelationshipChangesForNode::RelationshipChangesForNode()
{
}


RelationshipChangesForNode::~RelationshipChangesForNode()
{
	size_t len1 = outgoing.size();
	size_t len2 = incoming.size();
	size_t len3 = loops.size();

	for (size_t i = 0; i < len1; i++)
	{
		delete outgoing[i];
	}
	for (size_t i = 0; i < len2; i++)
	{
		delete incoming[i];
	}
	for (size_t i = 0; i < len3; i++)
	{
		delete loops[i];
	}
}

map<int, set<long>*> RelationshipChangesForNode::getOutgoing()
{
	return outgoing;
}

map<int, set<long>*> RelationshipChangesForNode::getIncoming()
{
	return incoming;
}

map<int, set<long>*> RelationshipChangesForNode::getLoops()
{
	return loops;
}

map<int, set<long>*> RelationshipChangesForNode::getTypeToRelMapForDirection(Direction direction)
{
	map<int /* Type */, set<long /* Id */>*> relTypeToRelsMap;
	switch (direction)
	{
		case Direction::INCOMING:
			relTypeToRelsMap = getIncoming();
			break;
		case Direction::OUTGOING:
			relTypeToRelsMap = getOutgoing();
			break;
		case Direction::BOTH:
			relTypeToRelsMap = getLoops();
			break;
		default:
			throw new invalid_argument("Unknown direction");
		}
	return relTypeToRelsMap;
}

void RelationshipChangesForNode::addRelationship(long relId, int typeId, Direction direction)
{
	map<int, set<long>*> relTypeToRelsMap = getTypeToRelMapForDirection(direction);
	map<int, set<long>*>::iterator iter = relTypeToRelsMap.find(typeId);

	set<long> *rels;
	if((iter) != relTypeToRelsMap.end())
	{
		rels = iter->second;
	}
	else
	{
		rels = new set<long>;
		relTypeToRelsMap[typeId] = rels;
	}

	rels->insert(relId);

	switch (direction)
	{
		case Direction::INCOMING:
			totalIncoming++;
			break;
		case Direction::OUTGOING:
			totalOutgoing++;
			break;
		case Direction::BOTH:
			totalLoops++;
			break;
		default:
			throw new invalid_argument("Unknown direction ");
	}
}

bool RelationshipChangesForNode::removeRelationship(long relId, int typeId, Direction direction)
{
	map<int, set<long>*> relTypeToRelsMap = getTypeToRelMapForDirection(direction);
	map<int, set<long>*>::iterator iter = relTypeToRelsMap.find(typeId);

	set<long> *rels;

	if (iter != relTypeToRelsMap.end())
	{
		rels = iter->second;

		if (rels->erase(relId))
		{
			if (rels->empty())
			{
				relTypeToRelsMap.erase(typeId);
			}

			switch (direction)
			{
			case Direction::INCOMING:
				totalIncoming--;
				break;
			case Direction::OUTGOING:
				totalOutgoing--;
				break;
			case Direction::BOTH:
				totalLoops--;
				break;
			default:
				throw new invalid_argument("Unknown direction ");
			}
			return true;
		}
	}
	return false;
}

void RelationshipChangesForNode::clear()
{
	// 清空三个Map表
	if (!outgoing.empty())
	{
		outgoing.clear();
	}
	if (!incoming.empty())
	{
		incoming.clear();
	}
	if (!loops.empty())
	{
		loops.clear();
	}
}
