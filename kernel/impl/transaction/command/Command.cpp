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

const Command::Mode Command::fromRecordState(bool created, bool inUse)
{
	if (!inUse)
	{
		return Command::Mode::DELETE;
	}
	if (created)
	{
		return Command::Mode::CREATE;
	}
	return Command::Mode::UPDATE;
}


template<class RECORD>
inline Command::BaseCommand<RECORD>::BaseCommand(RECORD before, RECORD after)
{
	setup(after.getId(), Mode.fromRecordState(after));
}

template<class RECORD>
inline RECORD Command::BaseCommand<RECORD>::getBefore()
{
	return before;
}

template<class RECORD>
inline RECORD Command::BaseCommand<RECORD>::getAfter()
{
	return after;
}


template<class RECORD>
inline const Command::Mode Command::fromRecordState(RECORD record)
{
	return fromRecordState(record.isCreated(), record.inUse());
}


template<class NodeRecord>
inline Command::NodeCommand<NodeRecord>::NodeCommand(NodeRecord before, NodeRecord after)
{
	Command::BaseCommand(before, after);
}


template<class RelationshipCommand>
inline Command::RelationshipCommand<RelationshipCommand>::RelationshipCommand(RelationshipRecord before, RelationshipRecord after)
{
	Command::BaseCommand(before, after);
}

