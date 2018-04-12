#pragma once
#include "AbstractBaseRecord.h"
#include "DynamicRecord.h"
#include <vector>
#include <string>
#include <sstream>
#include "Record.h"

using namespace std;

class TokenRecord: public AbstractBaseRecord
{
public:
	TokenRecord();
	virtual ~TokenRecord();
	TokenRecord(int id);
	virtual TokenRecord initialize(bool inUse, int nameId);
	void clear() override;
	bool isLight() const;
	int getNameId() const;
	void setNameId(int blockId);
	vector<DynamicRecord> getNameRecords() const;
	void addNameRecord(DynamicRecord record);
	void addNameRecords(vector<DynamicRecord> records);
	virtual string toString() const;

protected:
	virtual string simpleName() const;

private:
	int nameId;
	vector<DynamicRecord> nameRecords;
};

