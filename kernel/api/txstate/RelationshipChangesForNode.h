#pragma once
#include <map>
#include <set>
#include "../../../storageengine/api/Direction.h"
#include <stdexcept>

using namespace std;

class RelationshipChangesForNode
{
public:
	RelationshipChangesForNode();
	~RelationshipChangesForNode();
	map<int, set<long>*> getTypeToRelMapForDirection(Direction direction);
	void addRelationship(long relId, int typeId, Direction direction);
	bool removeRelationship(long relId, int typeId, Direction direction);
	void clear();


private:
	// 记录该点所有出度、入度、自指向的关系的 RelType -> Set<RelId> 的Map
	map<int, set<long>*> outgoing;
	map<int, set<long>*> incoming;
	map<int, set<long>*> loops;

	// 出度、入度和自指向关系的数量
	int totalOutgoing;
	int totalIncoming;
	int totalLoops;

	map<int, set<long>*> getOutgoing();
	map<int, set<long>*> getIncoming();
	map<int, set<long>*> getLoops();
	map<int, set<long>*> getTypeToRelMapForDirection(Direction direction);


};

