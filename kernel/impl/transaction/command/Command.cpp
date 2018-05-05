#include "Command.h"



Command::Command()
{
}


Command::~Command()
{
}

Command::Mode Command::getMode()
{
	return mode;
}

long Command::getKey()
{
	return key;
}

int Command::hashCode()
{
	return keyHash;
}

void Command::setup(long key, Mode mode)
{
	this->mode = mode;
	this->keyHash = (int)((key >> 32) ^ key);
	this->key = key;
}


template<class RECORD>
inline Command::BaseCommand<RECORD:public AbstractBaseRecord>::BaseCommand(RECORD before, RECORD after)
{
	//setup(after.getId(), Mode.fromRecordState(after));
}

template<class RECORD>
inline RECORD Command::BaseCommand<RECORD:public AbstractBaseRecord>::getBefore()
{
	return before;
}

template<class RECORD>
inline RECORD Command::BaseCommand<RECORD:public AbstractBaseRecord>::getAfter()
{
	return after;
}