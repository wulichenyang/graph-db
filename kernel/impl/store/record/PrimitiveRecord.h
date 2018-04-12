#pragma once
#include "AbstractBaseRecord.h"
#include "Record.h"

class PrimitiveRecord: public AbstractBaseRecord
{
public:
	PrimitiveRecord();
	virtual ~PrimitiveRecord();
	PrimitiveRecord(long id);
	PrimitiveRecord(long id, long nextProp);
	virtual long getNextProp() const;
	virtual void setNextProp(long nextProp);

protected:
	long nextProp;
	virtual void clear() override;
};

