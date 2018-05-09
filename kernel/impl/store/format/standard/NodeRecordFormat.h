#pragma once
#include "../RecordFormat.h"
#include "../../record/NodeRecord.h"
#include "../../../../../io/fs/ByteBuffer.h"
#include "../../../../../io/fs/FileChannel.h"
#include "../BaseRecordFormat.h"

class NodeRecordFormat:public RecordFormat<NodeRecord>
{
public:
	NodeRecordFormat();
	~NodeRecordFormat();

	void markAsUnused(ByteBuffer * buf);

	void read(NodeRecord * record, ByteBuffer * buf, int recordSize);
	void write(NodeRecord *record, ByteBuffer *buf, int recordSize);

private:
	bool isInUse(char byte);
};

