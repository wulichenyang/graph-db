#pragma once
#include "../../store/StoreType.h"
#include "../../store/id/IdSequence.h"
#include "../id/IdGenerator.h"

class RenewableBatchIdSequences
{
public:
	RenewableBatchIdSequences();
	~RenewableBatchIdSequences();

	RenewableBatchIdSequences(NeoStores *stores, int batchSize);
	long nextId(StoreType type);
	IdSequence *idGenerator(StoreType type);
	void close();

private:
	IdGenerator * types = new IdGenerator[StoreType::COUNTS - StoreType::NODE_LABEL + 1 ];
};

