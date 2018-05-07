#pragma once
template <class RECORD>
class RecordChange
{
public:
	RecordChange();
	// 析构map/changes会释放 *allChanges
	~RecordChange();
	RecordChange(PrimitiveLongObjectMap<RecordProxy<RECORD>*> *allChanges, IntCounter changeCounter,
		long key, RECORD record, Loader<RECORD> loader, bool created);
	long getKey();
	RECORD forChangingLinkage();
	RECORD forChangingData();

	// 返回当前record
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

	// 引用数加一，changed改变，加入map
	RECORD prepareForChange();
	void ensureHeavy();
	void ensureHasBeforeRecordImage();

};

