#pragma once
#include "RecordChange.h"

template <class RECORD>
class RecordChanges
{
public:
	RecordChanges();
	RecordChanges(Loader<RECORD> loader, IntCounter globalCounter);
	// Îö¹¹map/vector/recordChanges
	~RecordChanges();

	RecordChange<RECORD> *getIfLoaded(long key);
	RecordChange<RECORD> *getOrLoad(long key);
	void setTo(long key, RECORD newRecord);
	RecordChange<RECORD> *setRecord(long key, RECORD record);
	int changeSize();
	void close();
	RecordChange<RECORD> *create(long key);
	vector<RecordChange<RECORD>*> changes();

private:
	PrimitiveLongObjectMap<RecordChange<RECORD>*> *recordChanges;
	Loader<RECORD> loader;
	IntCounter changeCounter;
};

