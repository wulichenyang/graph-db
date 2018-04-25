#pragma once
#include "RelationshipChangesForNode.h"
#include "../util/diffsets/SuperDiffSets.h"
#include "TxState.h"
#include "PropertyContainerState.h"
#include "../../../storageengine/api/Direction.h"
#include "../../../kernel/impl/newapi/RelationshipDirection.h"

class NodeState:public PropertyContainerState
{
public:
	NodeState();
	~NodeState();
	NodeState(long id, TxState state);
	//SuperDiffSets<int> getOrCreateLabelDiffSets();
	void addRelationship(long relId, int typeId, Direction direction);
	void removeRelationship(long relId, int typeId, Direction direction);
	void clear();
	//void accept(NodeState.Visitor visitor);
	bool hasAddedRelationships();
	bool hasRemovedRelationships();
	//PrimitiveIntSet relationshipTypes();
	bool hasRelationshipChanges();
	vector<long> getAddedRelationships(Direction direction);
	vector<long> getAddedRelationships(Direction direction, int *relTypes);
	vector<long> getAddedRelationships();
	vector<long> getAddedRelationships(RelationshipDirection direction, int relType);

private:
	SuperDiffSets<int> labelDiffSets;
	RelationshipChangesForNode relationshipsAdded;
	RelationshipChangesForNode relationshipsRemoved;

	TxState state;
};

