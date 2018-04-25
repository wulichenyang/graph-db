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
	// ��¼�õ����г��ȡ���ȡ���ָ��Ĺ�ϵ�� RelType -> Set<RelId> ��Map
	map<int, set<long>*> outgoing;
	map<int, set<long>*> incoming;
	map<int, set<long>*> loops;

	// ���ȡ���Ⱥ���ָ���ϵ������
	int totalOutgoing;
	int totalIncoming;
	int totalLoops;

	map<int, set<long>*> getOutgoing();
	map<int, set<long>*> getIncoming();
	map<int, set<long>*> getLoops();
	map<int, set<long>*> getTypeToRelMapForDirection(Direction direction);


};

