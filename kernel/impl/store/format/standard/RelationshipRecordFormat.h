#pragma once
#include "../RecordFormat.h"
#include "../../record/RelationshipRecord.h"
#include "../../../../../io/fs/ByteBuffer.h"
#include "../../../../../io/fs/FileChannel.h"
#include "../BaseRecordFormat.h"

class RelationshipRecordFormat :public RecordFormat<RelationshipRecord>
{
public:
	RelationshipRecordFormat();
	~RelationshipRecordFormat();

	void markAsUnused(ByteBuffer * buf);

	void read(NodeRecord * record, ByteBuffer * buf, int recordSize);
	void write(NodeRecord *record, ByteBuffer *buf, int recordSize);

private:
	bool isInUse(char byte);
};

