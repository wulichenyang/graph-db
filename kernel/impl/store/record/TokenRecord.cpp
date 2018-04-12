#include "TokenRecord.h"



TokenRecord::TokenRecord()
{
}


TokenRecord::~TokenRecord()
{
}

TokenRecord::TokenRecord(int id):AbstractBaseRecord(id)
{
}

TokenRecord TokenRecord::initialize(bool inUse, int nameId)
{
	AbstractBaseRecord::initialize(inUse);
	this->nameId = nameId;
	this->nameRecords = vector<DynamicRecord>();
	return *this;
}

void TokenRecord::clear()
{
	initialize(false, (Record(Record::NO_NEXT_BLOCK)).getIntType());
}

bool TokenRecord::isLight() const
{
	return nameRecords.empty();
}

int TokenRecord::getNameId() const
{
	return nameId;
}

void TokenRecord::setNameId(int blockId)
{
	this->nameId = blockId;
}

vector<DynamicRecord> TokenRecord::getNameRecords() const
{
	return nameRecords;
}

void TokenRecord::addNameRecord(DynamicRecord record)
{
	nameRecords.push_back(record);
}

void TokenRecord::addNameRecords(vector<DynamicRecord> records)
{
	size_t len = records.size();

	for (size_t i = 0; i < len; i++) {
		addNameRecord(records[i]);
	}
}

string TokenRecord::toString() const
{
	stringstream ss;
	ss << simpleName() << "[" << getId() << "," << (inUse() ? "in" : "no")
		<< ",nameId=" << nameId;

	if (!isLight())
	{
		size_t len = nameRecords.size();
		for (size_t i = 0; i < len; i++) {
			ss << "," << nameRecords[i].toString();
		}
	}
	return ss.str();
}

string TokenRecord::simpleName() const
{
	return "initialName";
}
