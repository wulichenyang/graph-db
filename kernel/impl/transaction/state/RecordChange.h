#pragma once
template <class RECORD>
class RecordChange
{
public:
	RecordChange();
	// ����map/changes���ͷ� *allChanges
	~RecordChange();
	RecordChange(PrimitiveLongObjectMap<RecordProxy<RECORD>*> *allChanges, IntCounter changeCounter,
		long key, RECORD record, Loader<RECORD> loader, bool created);
	long getKey();
	RECORD forChangingLinkage();
	RECORD forChangingData();

	// ���ص�ǰrecord
	RECORD forReadingLinkage();
	RECORD forReadingData();
	bool isChanged();
	RECORD getBefore();
	boolean isCreated();

private:
	PrimitiveLongObjectMap<RecordChange<RECORD>*> *allChanges;
	IntCounter changeCounter;
	Loader<RECORD> loader;

	RECORD record;
	bool created;
	long key;

	RECORD before;
	bool changed;

	// ��������һ��changed�ı䣬����map
	RECORD prepareForChange();
	void ensureHeavy();
	void ensureHasBeforeRecordImage();

};

