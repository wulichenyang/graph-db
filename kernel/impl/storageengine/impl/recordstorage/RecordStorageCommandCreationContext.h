#pragma once
#include "../../../transaction/state/RelationshipCreator.h"
#include "../../../transaction/state/RelationshipDeleter.h"
#include "../../../store/id/RenewableBatchIdSequences.h"
#include "../../../store/NeoStores.h"

class RecordStorageCommandCreationContext
{
public:
	RecordStorageCommandCreationContext();
	~RecordStorageCommandCreationContext();
	RecordStorageCommandCreationContext(NeoStores *neoStores, int idBatchSize);

	long nextId(StoreType storeType);
	void close();
		
	NeoStores *neoStores;
	RelationshipCreator *relationshipCreator;
	RelationshipDeleter *relationshipDeleter;
	RenewableBatchIdSequences *idBatches;
};

