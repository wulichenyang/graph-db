#include "NodeRecordFormat.h"



NodeRecordFormat::NodeRecordFormat()
{
}


NodeRecordFormat::~NodeRecordFormat()
{
}

void NodeRecordFormat::markAsUnused(ByteBuffer *buf)
{

}

void NodeRecordFormat::read(NodeRecord * record, ByteBuffer * buf, int recordSize)
{
	char headerByte = buf->get();
	bool inUse = isInUse(headerByte);
	record->setInUse(inUse);

	long nextRel = buf->getInt() & 0xFFFFFFFFL;
	long nextProp = buf->getInt() & 0xFFFFFFFFL;

	long relModifier = (headerByte & 0xEL) << 31;
	long propModifier = (headerByte & 0xF0L) << 28;

	long lsbLabels = buf->getInt() & 0xFFFFFFFFL;
	long hsbLabels = buf->get() & 0xFF; // so that a negative byte won't fill the "extended" bits with ones.
	long labels = lsbLabels | (hsbLabels << 32);
	char extra = buf->get();
	bool dense = (extra & 0x1) > 0;

	record->initialize(inUse,
		BaseRecordFormat::longFromIntAndMod(nextProp, propModifier), dense,
		BaseRecordFormat::longFromIntAndMod(nextRel, relModifier), labels);

}

void NodeRecordFormat::write(NodeRecord * record, ByteBuffer * buf, int recordSize)
{
	buf->allocate(recordSize);
		
	if (record->inUse())
	{
		long nextRel = record->getNextRel();
		long nextProp = record->getNextProp();

		short relModifier = nextRel == (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType() ? 0 : (short)((nextRel & 0x700000000L) >> 31);
		short propModifier = nextProp == (Record(Record::NO_NEXT_PROPERTY)).getIntType() ? 0 : (short)((nextProp & 0xF00000000L) >> 28);

		// [    ,   x] in use bit
		// [    ,xxx ] higher bits for rel id
		// [xxxx,    ] higher bits for prop id
		short inUseUnsignedByte = Record(record->inUse() ? Record::IN_USE : Record::NOT_IN_USE).getByteType();
		inUseUnsignedByte = (short)(inUseUnsignedByte | relModifier | propModifier);

		buf->put(inUseUnsignedByte);
		buf->putInt((int)nextRel);
		buf->putInt((int)nextProp);

		// lsb of labels
		long labelField = record->getLabelField();
		buf->putInt((int)labelField);
		// msb of labels
		buf->put((char)((labelField & 0xFF00000000L) >> 32));

		char extra = record->isDense() ? (char)1 : (char)0;
		buf->put(extra);
	}
	// 只修改inUse部分
	else
	{
		markAsUnused(buf);
	}

	delete buf;
}
