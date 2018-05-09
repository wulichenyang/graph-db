#include "NodeRecord.h"



NodeRecord::NodeRecord(long id):PrimitiveRecord(id)
{
}

NodeRecord::~NodeRecord()
{
}

NodeRecord NodeRecord::initialize(bool inUse, long nextProp, bool dense, long nextRel, long labels)
{
	PrimitiveRecord::initialize(inUse);
	this->nextProp = nextProp;
	this->nextRel = nextRel;
	this->labels = labels;
	this->dense = dense;
	return *this;
}

NodeRecord::NodeRecord(long id, long nextRel, long nextProp)
{
	NodeRecord(id, false, nextRel, nextProp, 0);
}

NodeRecord::NodeRecord(long id, bool inUse, long nextRel, long nextProp, long labels):PrimitiveRecord(id, nextProp)
{
	setInUse(inUse);
	this->nextRel = nextRel;
	this->labels = labels;
}

NodeRecord::NodeRecord(long id, long nextRel, long nextProp, bool inUse)
{
	NodeRecord(id, nextRel, nextProp);
	setInUse(inUse);
}

void NodeRecord::clear()
{
	initialize(false, (Record(Record::NO_NEXT_PROPERTY)).getIntType(), (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType(), (Record(Record::NO_LABELS_FIELD)).getIntType());
}

long NodeRecord::getNextRel() const
{
	return nextRel;
}

void NodeRecord::setNextRel(long nextRel)
{
	this->nextRel = nextRel;
}

void NodeRecord::setLabelField(long labels, vector<DynamicRecord> dynamicRecords)
{
	this->labels = labels;
	this->dynamicLabelRecords = dynamicLabelRecords;
	this->isLightFlag = dynamicRecords.empty();
}

long NodeRecord::getLabelField() const
{
	return labels;
}

bool NodeRecord::isLight() const
{
	return isLightFlag;
}

vector<DynamicRecord> NodeRecord::getDynamicLabelRecords() const
{
	return dynamicLabelRecords;
}

string NodeRecord::toString() const
{
	string nextRel = nextRel;
	string lightHeavyInfo = isLightFlag ? "light" : "noLight";
	stringstream ss;

	ss << "Node[" << getId() <<
		",used=" << inUse() <<
		"," << ",prop=" << getNextProp() <<
		",labels=..]" << endl;

	return ss.str();
}
