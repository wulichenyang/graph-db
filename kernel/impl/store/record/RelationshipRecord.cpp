#include "RelationshipRecord.h"


RelationshipRecord::RelationshipRecord()
{
}


RelationshipRecord::~RelationshipRecord()
{
}

RelationshipRecord::RelationshipRecord(long id, long firstNode, long secondNode, int type)
	:PrimitiveRecord(id)
{
	this->firstNode = firstNode;
	this->secondNode = secondNode;
	this->type = type;
}

RelationshipRecord::RelationshipRecord(long id, bool inUse, long firstNode, long secondNode, int type, long firstPrevRel, long firstNextRel, long secondPrevRel, long secondNextRel, bool firstInFirstChain, bool firstInSecondChain)
{
	RelationshipRecord(id, firstNode, secondNode, type);
	setInUse(inUse);
	this->firstPrevRel = firstPrevRel;
	this->firstNextRel = firstNextRel;
	this->secondPrevRel = secondPrevRel;
	this->secondNextRel = secondNextRel;
	this->firstInFirstChain = firstInFirstChain;
	this->firstInSecondChain = firstInSecondChain;
}

RelationshipRecord::RelationshipRecord(long id):PrimitiveRecord(id)
{
}

RelationshipRecord RelationshipRecord::initialize(bool inUse, long nextProp, long firstNode, long secondNode, int type, long firstPrevRel, long firstNextRel, long secondPrevRel, long secondNextRel, bool firstInFirstChain, bool firstInSecondChain)
{
	PrimitiveRecord::initialize(inUse);
	this->nextProp = nextProp;
	this->firstNode = firstNode;
	this->secondNode = secondNode;
	this->type = type;
	this->firstPrevRel = firstPrevRel;
	this->firstNextRel = firstNextRel;
	this->secondPrevRel = secondPrevRel;
	this->secondNextRel = secondNextRel;
	this->firstInFirstChain = firstInFirstChain;
	this->firstInSecondChain = firstInSecondChain;

	return *this;
}

void RelationshipRecord::clear()
{
	initialize(false, (Record(Record::NO_NEXT_PROPERTY)).getIntType(), -1, -1, -1,
	1, (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType(),
	1, (Record(Record::NO_NEXT_RELATIONSHIP)).getIntType(), true, true);
}

void RelationshipRecord::setLinks(long firstNode, long secondNode, int type)
{
	this->firstNode = firstNode;
	this->secondNode = secondNode;
	this->type = type;
}

long RelationshipRecord::getFirstNode() const
{
	return firstNode;
}

void RelationshipRecord::setFirstNode(long firstNode)
{
	this->firstNode = firstNode;
}

long RelationshipRecord::getSecondNode() const
{
	return secondNode;
}

void RelationshipRecord::setSecondNode(long secondNode)
{
	this->secondNode = secondNode;
}

int RelationshipRecord::getType() const
{
	return type;
}

void RelationshipRecord::setType(int type)
{
	this->type = type;
}

long RelationshipRecord::getFirstPrevRel() const
{
	return firstPrevRel;
}

void RelationshipRecord::setFirstPrevRel(long firstPrevRel)
{
	this->firstPrevRel = firstPrevRel;
}

long RelationshipRecord::getFirstNextRel() const
{
	return firstNextRel;
}

void RelationshipRecord::setFirstNextRel(long firstNextRel)
{
	this->firstNextRel = firstNextRel;
}

long RelationshipRecord::getSecondPrevRel() const
{
	return secondPrevRel;
}

void RelationshipRecord::setSecondPrevRel(long secondPrevRel)
{
	this->secondPrevRel = secondPrevRel;
}

long RelationshipRecord::getSecondNextRel() const
{
	return secondNextRel;
}

void RelationshipRecord::setSecondNextRel(long secondNextRel)
{
	this->secondNextRel = secondNextRel;
}

bool RelationshipRecord::isFirstInFirstChain() const
{
	return firstInFirstChain;
}

void RelationshipRecord::setFirstInFirstChain(bool firstInFirstChain)
{
	this->firstInFirstChain = firstInFirstChain;
}

bool RelationshipRecord::isFirstInSecondChain() const
{
	return firstInSecondChain;
}

void RelationshipRecord::setFirstInSecondChain(bool firstInSecondChain)
{
	this->firstInSecondChain = firstInSecondChain;
}

string RelationshipRecord::toString()
{
	stringstream ss;
	ss << "Relationship[" << getId() <<
		",used=" << inUse() <<
		",source=" << firstNode <<
		",target=" << secondNode <<
		"t,y=pe" << type <<
		(firstInFirstChain ? ",sCount=" : ",sPrev=") << firstPrevRel <<
		",sNext=" << firstNextRel <<
		(firstInSecondChain ? ",tCount=" : ",tPrev=") << secondPrevRel <<
		",tNext=" << secondNextRel <<
		",prop=" << getNextProp() <<
		(firstInFirstChain ? ", sFirst" : ",!sFirst") <<
		(firstInSecondChain ? ", tFirst" : ",!tFirst") << "]";

	return ss.str();
}
