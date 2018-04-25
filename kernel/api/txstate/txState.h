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
	void accept(TxStateVisitor visitor);

private:
	static LabelState LABEL_STATE;
	static NodeState NODE_STATE;
	static RelationshipState RELATIONSHIP_STATE;

	// ���浱ǰ�ڵ㡢��ǩ����ϵ��״̬����id��long������
	PrimitiveLongObjectMap<LabelState> labelStatesMap;
	PrimitiveLongObjectMap<NodeState> nodeStatesMap;
	PrimitiveLongObjectMap<RelationshipState> relationshipStatesMap;

	// ���洴���ı�ǩ�����Լ�����ϵ���͵�Token״̬����id(int)����
	PrimitiveIntObjectMap<string> createdLabelTokens;
	PrimitiveIntObjectMap<string> createdPropertyKeyTokens;
	PrimitiveIntObjectMap<string> createdRelationshipTypeTokens;

	RemovalsCountingDiffSets nodes;
	RemovalsCountingDiffSets relationships;

	bool hasChanges;
	bool hasDataChanges;
};

