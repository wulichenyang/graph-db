#pragma once
#include <map>
#include <set>
#include "../../../storageengine/api/Direction.h"
#include "../../impl/newapi/RelationshipDirection.h"
#include <stdexcept>
#include <stdarg.h>
#include <vector>
#include "../util/Computer.h"

using namespace std;


class RelationshipChangesForNode
{
public:
	RelationshipChangesForNode();
	~RelationshipChangesForNode();
	map<int, set<long>*> getTypeToRelMapForDirection(Direction direction);
	void addRelationship(long relId, int typeId, Direction direction);
	bool removeRelationship(long relId, int typeId, Direction direction);
	set<long> getRelationships(Direction direction);
	set<long> getRelationships(Direction direction, int *types);
	set<long> getRelationships();
	set<long> *getRelationships(RelationshipDirection direction, int type);
	set<long> *primitiveIdsByType(map<int, set<long>*> map, int type);
	set<long> primitiveId(map<int, set<long>*> map);
	set<long> diffs(int *types, map<int, set<long>*> m1, map<int, set<long>*> m2);
	set<long> diffs(int *types, map<int, set<long>*> m1, map<int, set<long>*> m2, map<int, set<long>*> m3);
	set<long> getAllTypes(map<int, set<long>*> m1, map<int, set<long>*> m2);
	set<long> getAllTypes(map<int, set<long>*> m1, map<int, set<long>*> m2, map<int, set<long>*> m3);

	void clear();

	int getTotalOutgoing();
	int getTotalIncoming();
	int getTotalLoops();

private:
	// 记录该点所有出度、入度、自指向的关系的 RelType -> Set<RelId> 的Map
	map<int, set<long>*> outgoing;
	map<int, set<long>*> incoming;
	map<int, set<long>*> loops;

	// 出度、入度和自指向关系的数量
	int totalOutgoing = 0;
	int totalIncoming = 0;
	int totalLoops = 0;

	map<int, set<long>*> getOutgoing();
	map<int, set<long>*> getIncoming();
	map<int, set<long>*> getLoops();
	map<int, set<long>*> getTypeToRelMapForDirection(Direction direction);


};

