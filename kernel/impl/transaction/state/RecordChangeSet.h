#pragma once
#include "RecordChanges.h"

class RecordChangeSet
{
public:
	RecordChangeSet();
	// Îö¹¹intCount
	RecordChangeSet(
		Loader<NodeRecord> *nodeLoader,
		Loader<RelationshipRecord> *relationshipLoader,
		Loader<LabelTokenRecord> *labelTokenLoader,
		Loader<RelationshipTypeTokenRecord> *relationshipTypeTokenLoader);
	~RecordChangeSet();

	RecordChanges<NodeRecord> *getNodeRecords();
	RecordChanges<RelationshipRecord> *getRelRecords();
	RecordChanges<LabelTokenRecord> *getLabelTokenChanges();
	RecordChanges<RelationshipTypeTokenRecord> *getRelationshipTypeTokenChanges(); 
	
	bool hasChanges();
	int changeSize();
	void close();

private:
	RecordChanges<NodeRecord> *nodeRecords;
	RecordChanges<RelationshipRecord> *relRecords;
	RecordChanges<LabelTokenRecord> *labelTokenChanges;
	RecordChanges<RelationshipTypeTokenRecord> *relationshipTypeTokenChanges;
	IntCounter changeCounter = new IntCounter();
};

