#pragma once
class AbstractBaseRecord
{
public:
	~AbstractBaseRecord();

	virtual void clear();
	virtual long getId() const;
	virtual void setId(long id) final;
	virtual bool inUse() const final;
	virtual void setInUse(bool inUse);
	virtual void setCreated() final;
	virtual bool isCreated() const final;

protected:
	AbstractBaseRecord(long id);
	AbstractBaseRecord initialize(bool inUse);

private:
	long id;
	bool inUseFlag;
	bool created;

};

