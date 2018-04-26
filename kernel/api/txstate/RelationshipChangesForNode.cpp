#include "RelationshipChangesForNode.h"



RelationshipChangesForNode::RelationshipChangesForNode()
{
}


RelationshipChangesForNode::~RelationshipChangesForNode()
{
	for (map<int, set<long>*>::iterator it = outgoing.begin(); it != outgoing.end(); it++)
	{
		delete it->second;
	}
	for (map<int, set<long>*>::iterator it = incoming.begin(); it != incoming.end(); it++)
	{
		delete it->second;
	}
	for (map<int, set<long>*>::iterator it = loops.begin(); it != loops.end(); it++)
	{
		delete it->second;
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

set<long> RelationshipChangesForNode::getRelationships(Direction direction)
{
	return getRelationships(direction, nullptr);
}

set<long> RelationshipChangesForNode::getRelationships(Direction direction, int * types)
{
	if (types == nullptr) {
		switch (direction)
		{
		case Direction::INCOMING:
			return incoming.size() != 0 || loops.size() != 0 ?
				getAllTypes(incoming, loops) : set<long>();
		case Direction::OUTGOING:
			return outgoing.size() != 0 || loops.size() != 0 ?
				getAllTypes(outgoing, loops) : set<long>();
		case Direction::BOTH:
			return outgoing.size() != 0 || incoming.size() != 0 || loops.size() != 0 ?
				getAllTypes(outgoing, incoming, loops) : set<long>();
		default:
			throw new invalid_argument("Unknown direction");
		}
	}

	switch (direction)
	{
	case Direction::INCOMING:
			return incoming.size()!= 0 || loops.size()!=0 ? 
				diffs(types, incoming, loops) : set<long>();
	case Direction::OUTGOING:
			return outgoing.size() != 0 || loops.size() != 0 ?
				diffs(types, outgoing, loops) : set<long>();
	case Direction::BOTH:
			return outgoing.size() != 0 || incoming.size() != 0 || loops.size() != 0 ?
				diffs(types, outgoing, incoming, loops) : set<long>();
		default:
			throw new invalid_argument("Unknown direction");
	}
}

set<long> RelationshipChangesForNode::getRelationships()
{
	set<long> s = set<long>();

	set<long> s1 = primitiveId(incoming);
	set<long> s2 = primitiveId(outgoing);
	set<long> s3 = primitiveId(loops);

	s.insert(s1.begin(), s1.end());
	s.insert(s2.begin(), s2.end());
	s.insert(s3.begin(), s3.end());

	return s;
}

set<long> *RelationshipChangesForNode::getRelationships(RelationshipDirection direction, int type)
{
	switch (direction)
	{
	case RelationshipDirection::INCOMING:
		return incoming.size() != 0 ? primitiveIdsByType(incoming, type) : new set<long>();
	case RelationshipDirection::OUTGOING:
		return outgoing.size() != 0 ? primitiveIdsByType(outgoing, type) : new set<long>();
	case RelationshipDirection::LOOP:
		return loops.size() != 0 ? primitiveIdsByType(loops, type) : new set<long>();
	default:
		throw new invalid_argument("Unknown direction");
	}
}

set<long>* RelationshipChangesForNode::primitiveIdsByType(map<int, set<long>*> _map, int type)
{
	map<int, set<long>*>::iterator iter =_map.find(type);
	if (iter == _map.end()) 
	{
		return new set<long>();
	}
	return iter->second;
}

set<long> RelationshipChangesForNode::primitiveId(map<int, set<long>*> m)
{
	set<long> s = set<long>();
	for (map<int, set<long>*>::iterator it = m.begin(); it != m.end(); it++)
		s.insert(it->second->begin(), it->second->end());
	return s;
}

set<long> RelationshipChangesForNode::diffs(int *types, map<int, set<long>*> m1, map<int, set<long>*> m2)
{
	set<long> s;
	set<long> temp;
	int typeNum = Computer::arrayLen(types);

	for (size_t i = 0; i < typeNum; i++)
	{
		temp = *(m1[types[i]]);
		s.insert(temp.begin(), temp.end());

		temp = *(m2[types[i]]);
		s.insert(temp.begin(), temp.end());
	}

	return s;
}

set<long> RelationshipChangesForNode::diffs(int * types, map<int, set<long>*> m1, map<int, set<long>*> m2, map<int, set<long>*> m3)
{
	set<long> s;
	set<long> temp;
	int typeNum = Computer::arrayLen(types);

	for (size_t i = 0; i < typeNum; i++)
	{
		temp = *(m1[types[i]]);
		s.insert(temp.begin(), temp.end());

		temp = *(m2[types[i]]);
		s.insert(temp.begin(), temp.end());

		temp = *(m3[types[i]]);
		s.insert(temp.begin(), temp.end());
	}

	return s;
}

set<long> RelationshipChangesForNode::getAllTypes(map<int, set<long>*> m1, map<int, set<long>*> m2)
{
	set<long> s;
	set<long> temp;

	map<int, set<long>*>::iterator it = m1.begin();

	for (; it != m1.end(); it++) 
	{
		temp = *(it->second);
		s.insert(temp.begin(), temp.end());
	}

	it = m2.begin();

	for (; it != m2.end(); it++)
	{
		temp = *(it->second);
		s.insert(temp.begin(), temp.end());
	}

	return s;
}

set<long> RelationshipChangesForNode::getAllTypes(map<int, set<long>*> m1, map<int, set<long>*> m2, map<int, set<long>*> m3)
{
	set<long> s;
	set<long> temp;

	map<int, set<long>*>::iterator it = m1.begin();

	for (; it != m1.end(); it++)
	{
		temp = *(it->second);
		s.insert(temp.begin(), temp.end());
	}

	it = m2.begin();

	for (; it != m2.end(); it++)
	{
		temp = *(it->second);
		s.insert(temp.begin(), temp.end());
	}

	it = m3.begin();

	for (; it != m3.end(); it++)
	{
		temp = *(it->second);
		s.insert(temp.begin(), temp.end());
	}

	return s;
}



void RelationshipChangesForNode::clear()
{
	for (map<int, set<long>*>::iterator it = outgoing.begin(); it != outgoing.end(); it++)
	{
		delete it->second;
	}
	for (map<int, set<long>*>::iterator it = incoming.begin(); it != incoming.end(); it++)
	{
		delete it->second;
	}
	for (map<int, set<long>*>::iterator it = loops.begin(); it != loops.end(); it++)
	{
		delete it->second;
	}

	// 清空三个Map表和数量
	if (!outgoing.empty())
	{
		outgoing.clear();
		totalOutgoing = 0;
	}
	if (!incoming.empty())
	{
		incoming.clear();
		totalIncoming = 0;
	}
	if (!loops.empty())
	{
		loops.clear();
		totalLoops = 0;
	}
}

int RelationshipChangesForNode::getTotalOutgoing()
{
	return totalOutgoing;
}

int RelationshipChangesForNode::getTotalIncoming()
{
	return totalIncoming;
}

int RelationshipChangesForNode::getTotalLoops()
{
	return totalLoops;
}
