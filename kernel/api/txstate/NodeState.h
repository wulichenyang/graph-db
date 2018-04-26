#pragma once
#include "RelationshipChangesForNode.h"
#include "../util/diffsets/SuperDiffSets.h"
#include "TxState.h"
#include "PropertyContainerState.h"
#include "../../../storageengine/api/Direction.h"
#include "../../../kernel/impl/newapi/RelationshipDirection.h"

class NodeState :public PropertyContainerState
{
public:
	NodeState();
	~NodeState();
	NodeState(long id, TxState *state);
	//SuperDiffSets<int> getOrCreateLabelDiffSets();
	void addRelationship(long relId, int typeId, Direction direction);
	void removeRelationship(long relId, int typeId, Direction direction);
	void clear();
	//void accept(NodeState.Visitor visitor);
	bool hasAddedRelationships();
	bool hasRemovedRelationships();
	//PrimitiveIntSet relationshipTypes();
	bool hasRelationshipChanges();
	set<long> *getAddedRelationships(Direction direction);
	set<long> *getAddedRelationships(Direction direction, int *relTypes);
	set<long> *getAddedRelationships();
	set<long> *getAddedRelationships(RelationshipDirection direction, int relType);

private:
	SuperDiffSets<int> labelDiffSets;
	RelationshipChangesForNode relationshipsAdded;
	RelationshipChangesForNode relationshipsRemoved;
	TxState *state;
};