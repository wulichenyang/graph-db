#include "RelationshipRecord.h"



RelationshipRecord::RelationshipRecord()
{
}


RelationshipRecord::~RelationshipRecord()
{
}

void RelationshipRecord::setFirstInSecondChain(bool firstInSecondChain)
{
}

string RelationshipRecord::toString()
{
	stringstream ss;
	ss << "Relationship[" << getId() <<
		",used=" << inUse() <<
		",source=" << firstNode <<
		",target=" << secondNode <<
		",type=" << type <<
		(firstInFirstChain ? ",sCount=" : ",sPrev=") << firstPrevRel <<
		",sNext=" << firstNextRel <<
		(firstInSecondChain ? ",tCount=" : ",tPrev=") << secondPrevRel <<
		",tNext=" << secondNextRel <<
		",prop=" << getNextProp() <<
		(firstInFirstChain ? ", sFirst" : ",!sFirst") <<
		(firstInSecondChain ? ", tFirst" : ",!tFirst") << "]";

	return ss.str();
}
