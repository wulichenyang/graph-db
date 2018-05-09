#include "RelationshipRecordFormat.h"



RelationshipRecordFormat::RelationshipRecordFormat()
{
}


RelationshipRecordFormat::~RelationshipRecordFormat()
{
}

void RelationshipRecordFormat::read(RelationshipRecord * record, ByteBuffer * buf, int recordSize)
{
	char headerByte = buf->get();
	bool inUse = isInUse(headerByte);
	record->setInUse(inUse);

	// [    ,   x] in use flag
	// [    ,xxx ] first node high order bits
	// [xxxx,    ] next prop high order bits
	long firstNode = buf->getInt() & 0xFFFFFFFFL;
	long firstNodeMod = (headerByte & 0xEL) << 31;

	long secondNode = buf->getInt() & 0xFFFFFFFFL;

	// [ xxx,    ][    ,    ][    ,    ][    ,    ] second node high order bits,     0x70000000
	// [    ,xxx ][    ,    ][    ,    ][    ,    ] first prev rel high order bits,  0xE000000
	// [    ,   x][xx  ,    ][    ,    ][    ,    ] first next rel high order bits,  0x1C00000
	// [    ,    ][  xx,x   ][    ,    ][    ,    ] second prev rel high order bits, 0x380000
	// [    ,    ][    , xxx][    ,    ][    ,    ] second next rel high order bits, 0x70000
	// [    ,    ][    ,    ][xxxx,xxxx][xxxx,xxxx] type
	long typeInt = buf->getInt();
	long secondNodeMod = (typeInt & 0x70000000L) << 4;
	int type = (int)(typeInt & 0xFFFF);

	long firstPrevRel = buf->getInt() & 0xFFFFFFFFL;
	long firstPrevRelMod = (typeInt & 0xE000000L) << 7;

	long firstNextRel = buf->getInt() & 0xFFFFFFFFL;
	long firstNextRelMod = (typeInt & 0x1C00000L) << 10;

	long secondPrevRel = buf->getInt() & 0xFFFFFFFFL;
	long secondPrevRelMod = (typeInt & 0x380000L) << 13;

	long secondNextRel = buf->getInt() & 0xFFFFFFFFL;
	long secondNextRelMod = (typeInt & 0x70000L) << 16;

	long nextProp = buf->getInt() & 0xFFFFFFFFL;
	long nextPropMod = (headerByte & 0xF0L) << 28;

	char extraByte = buf->get();

	record->initialize(inUse,
		BaseRecordFormat::longFromIntAndMod(nextProp, nextPropMod),
		BaseRecordFormat::longFromIntAndMod(firstNode, firstNodeMod),
		BaseRecordFormat::longFromIntAndMod(secondNode, secondNodeMod),
		type,
		BaseRecordFormat::longFromIntAndMod(firstPrevRel, firstPrevRelMod),
		BaseRecordFormat::longFromIntAndMod(firstNextRel, firstNextRelMod),
		BaseRecordFormat::longFromIntAndMod(secondPrevRel, secondPrevRelMod),
		BaseRecordFormat::longFromIntAndMod(secondNextRel, secondNextRelMod),
		(extraByte & 0x1) != 0,
		(extraByte & 0x2) != 0);
}

void RelationshipRecordFormat::write(RelationshipRecord * record, ByteBuffer * buf, int recordSize)
{
	buf->allocate(recordSize);

	if (record->inUse())
	{
		long firstNode = record->getFirstNode();
		short firstNodeMod = (short)((firstNode & 0x700000000L) >> 31);

		long secondNode = record->getSecondNode();
		long secondNodeMod = (secondNode & 0x700000000L) >> 4;

		long firstPrevRel = record->getFirstPrevRel();
		long firstPrevRelMod = firstPrevRel == (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType() ? 0 : (firstPrevRel & 0x700000000L) >> 7;

		long firstNextRel = record->getFirstNextRel();
		long firstNextRelMod = firstNextRel == (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType() ? 0 : (firstNextRel & 0x700000000L) >> 10;

		long secondPrevRel = record->getSecondPrevRel();
		long secondPrevRelMod = secondPrevRel == (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType() ? 0 : (secondPrevRel & 0x700000000L) >> 13;

		long secondNextRel = record->getSecondNextRel();
		long secondNextRelMod = secondNextRel == (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType() ? 0 : (secondNextRel & 0x700000000L) >> 16;

		long nextProp = record->getNextProp();
		long nextPropMod = nextProp == (Record(Record::NO_NEXT_PROPERTY)).getIntType() ? 0 : (nextProp & 0xF00000000L) >> 28;

		// [    ,   x] in use flag
		// [    ,xxx ] first node high order bits
		// [xxxx,    ] next prop high order bits
		short inUseUnsignedByte = (short)((Record(record->inUse() ? Record::IN_USE :
			Record::NOT_IN_USE)).getByteType() | firstNodeMod | nextPropMod);

		// [ xxx,    ][    ,    ][    ,    ][    ,    ] second node high order bits,     0x70000000
		// [    ,xxx ][    ,    ][    ,    ][    ,    ] first prev rel high order bits,  0xE000000
		// [    ,   x][xx  ,    ][    ,    ][    ,    ] first next rel high order bits,  0x1C00000
		// [    ,    ][  xx,x   ][    ,    ][    ,    ] second prev rel high order bits, 0x380000
		// [    ,    ][    , xxx][    ,    ][    ,    ] second next rel high order bits, 0x70000
		// [    ,    ][    ,    ][xxxx,xxxx][xxxx,xxxx] type
		int typeInt = (int)(record->getType() | secondNodeMod | firstPrevRelMod | firstNextRelMod | secondPrevRelMod | secondNextRelMod);

		// [    ,   x] 1:st in start node chain, 0x1
		// [    ,  x ] 1:st in end node chain,   0x2
		long firstInStartNodeChain = record->isFirstInFirstChain() ? 0x1 : 0;
		long firstInEndNodeChain = record->isFirstInSecondChain() ? 0x2 : 0;
		char extraByte = (char)(firstInEndNodeChain | firstInStartNodeChain);

		buf->put((char)inUseUnsignedByte);
		buf->putInt((int)firstNode);
		buf->putInt((int)secondNode);
		buf->putInt(typeInt);
		buf->putInt((int)firstPrevRel);
		buf->putInt((int)firstNextRel);
		buf->putInt((int)secondPrevRel);
		buf->putInt((int)secondNextRel);
		buf->putInt((int)nextProp);
		buf->put(extraByte);
	}

	// 只修改inUse部分
	else
	{
		markAsUnused(buf);
	}
}

bool RelationshipRecordFormat::isInUse(char byte)
{
	return false;
}
