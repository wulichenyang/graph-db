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
	class BaseCommand:public Command
	{
	public:
		BaseCommand(RECORD before, RECORD after);
		RECORD getBefore();
		RECORD getAfter();

	protected:
		RECORD before;
		RECORD after;
	};

	template <class NodeRecord>
	class NodeCommand :public Command::BaseCommand {
	public:
		NodeCommand(NodeRecord before, NodeRecord after);
		bool handle(CommandVisitor handler);

	};

	template <class RelationshipCommand> 
	class RelationshipCommand :public Command::BaseCommand {
	public:
		RelationshipCommand(RelationshipRecord before, RelationshipRecord after);
		bool handle(CommandVisitor handler);

	};

public:
	Command();
	~Command();
	Mode getMode();
	long getKey();
	int hashCode();

protected:
	void setup(long key, Mode mode);
	template <class RECORD>
	const Command::Mode Command::fromRecordState(RECORD record);
	const static Command::Mode fromRecordState(bool created, bool inUse);
private:
	int keyHash;
	long key;
	Mode mode;
};
