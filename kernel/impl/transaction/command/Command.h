#pragma once
#include "../../store/record/AbstractBaseRecord.h"
class Command
{

	enum Mode
	{
		CREATE,
		UPDATE,
		DELETE
	};

	enum Version
	{
		BEFORE,
		AFTER
	};

	template <class RECORD>
	class BaseCommand<RECORD:public AbstractBaseRecord>:public Command
	{
	public:
		BaseCommand(RECORD before, RECORD after);
		RECORD getBefore();
		RECORD getAfter();

	protected:
		RECORD before;
		RECORD after;
	};

public:
	Command();
	~Command();
	Mode getMode();
	long getKey();
	int hashCode();

protected:
	void setup(long key, Mode mode);

private:
	int keyHash;
	long key;
	Mode mode;
};
