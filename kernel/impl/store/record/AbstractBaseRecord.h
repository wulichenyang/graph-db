#pragma once
class AbstractBaseRecord
{
public:
	AbstractBaseRecord();
	AbstractBaseRecord(long id);
	virtual ~AbstractBaseRecord();

	virtual void clear();
	virtual long getId() const;
	virtual void setId(long id) final;
	virtual bool inUse() const final;
	virtual void setInUse(bool inUse);
	virtual void setCreated() final;
	virtual bool isCreated() const final;

protected:
	long id;
	bool inUseFlag;
	bool created;
	AbstractBaseRecord initialize(bool inUse);

};

