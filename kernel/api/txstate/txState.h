#pragma once
#include "../../../storageengine/api/txstate/TxStateVisitor.h"
#include "PrimitiveLongObjectMap.h"
#include "../util/diffsets/DiffSets.h"
#include "RemovalsCountingDiffSets.h"
#include "RemovalsCountingRelationshipsDiffSets.h"

class TxState
{
public:
	TxState();
	~TxState();
	void accept(TxStateVisitor visitor);
};

