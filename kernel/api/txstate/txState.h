#pragma once
#include "../../../storageengine/api/txstate/TxStateVisitor.h"
#include "PrimitiveLongObjectMap.h"
#include "RemovalsCountingDiffSets.h"
#include "RemovalsCountingRelationshipsDiffSets.h"
#include "NodeState.h"
#include "RelationshipState.h"
#include "LabelState.h"
#include "PrimitiveIntObjectMap.h"
#include <string>

using namespace std;

class TxState
{
public:
	TxState();
	~TxState();
	void nodeDoCreate(long nodeId);
	RemovalsCountingDiffSets getNodes();
	RemovalsCountingDiffSets getRelationships();
	void accept(TxStateVisitor visitor);
	void changed();
	void dataChanged();
	bool ifHasChanges();
	void nodeDoDelete(long nodeId);
	SuperDiffSets<int> getLabelStateNodeDiffSets(long nodeId);
	bool nodeIsDeletedInThisTx(long nodeId);
	bool nodeIsAddedInThisTx(long nodeId);
	void relationshipDoCreate(long id, int relationshipTypeId, long startNodeId, long endNodeId);
	void relationshipDoDelete(long id, int type, long startNodeId, long endNodeId);
private:
	static LabelState LABEL_STATE;
	static NodeState NODE_STATE;
	static RelationshipState RELATIONSHIP_STATE;

	// 保存当前节点、标签、关系的状态，用id（long）索引
	PrimitiveLongObjectMap<LabelState> labelStatesMap;
	PrimitiveLongObjectMap<NodeState> nodeStatesMap;
	PrimitiveLongObjectMap<RelationshipState> relationshipStatesMap;

	// 保存创建的标签、属性键、关系类型的Token状态，用id(int)索引
	PrimitiveIntObjectMap<string> createdLabelTokens;
	PrimitiveIntObjectMap<string> createdPropertyKeyTokens;
	PrimitiveIntObjectMap<string> createdRelationshipTypeTokens;

	NodeState *getOrCreateNodeState(long nodeId);
	RelationshipState *getOrCreateRelationshipState(long relationshipId);


	RemovalsCountingDiffSets nodes;
	RemovalsCountingDiffSets relationships;

	bool hasChanges;
	bool hasDataChanges;


};

