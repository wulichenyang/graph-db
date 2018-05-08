#pragma once
#include "PrimitiveRecord.h"
#include "DynamicRecord.h"
#include <vector>
#include <sstream>

using namespace std;

class NodeRecord: public PrimitiveRecord
{
public:
	NodeRecord(long id);
	~NodeRecord();
	NodeRecord initialize(bool inUse, long nextProp, long nextRel, long labels);
	NodeRecord(long id, long nextRel, long nextProp);
	NodeRecord(long id, bool inUse, long nextRel, long nextProp, long labels);
	NodeRecord(long id, long nextRel, long nextProp, bool inUse);
	void clear() override;
	long getNextRel() const;
	void setNextRel(long nextRel);
	void setLabelField(long labels, vector<DynamicRecord> dynamicRecords);
	long getLabelField() const;
	bool isLight() const;
	vector<DynamicRecord> getDynamicLabelRecords() const;
	string toString() const;
	bool isDense();
private:
	long nextRel;
	long labels;
	vector<DynamicRecord> dynamicLabelRecords;
	bool isLightFlag;
};

