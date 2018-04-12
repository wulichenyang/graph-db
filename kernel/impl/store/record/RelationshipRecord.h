#pragma once
#include "PrimitiveRecord.h"
#include <string>
#include <sstream>

using namespace std;

class RelationshipRecord: PrimitiveRecord
{
public:
	RelationshipRecord();
	~RelationshipRecord();
	RelationshipRecord(long id, long firstNode, long secondNode, int type);
	RelationshipRecord(long id, bool inUse, long firstNode, long secondNode, int type,
		long firstPrevRel, long firstNextRel, long secondPrevRel, long secondNextRel,
		bool firstInFirstChain, bool firstInSecondChain);
	RelationshipRecord(long id);
	RelationshipRecord initialize(bool inUse, long nextProp, long firstNode, long secondNode,
		int type, long firstPrevRel, long firstNextRel, long secondPrevRel, long secondNextRel,
		bool firstInFirstChain, bool firstInSecondChain);
	void clear();
	void setLinks(long firstNode, long secondNode, int type);
	long getFirstNode() const;
	void setFirstNode(long firstNode);
	long getSecondNode() const;
	void setSecondNode(long secondNode);
	int getType() const;
	void setType(int type);
	long getFirstPrevRel() const;
	void setFirstPrevRel(long firstPrevRel);
	long getFirstNextRel() const;
	void setFirstNextRel(long firstNextRel);
	long getSecondPrevRel() const;
	void setSecondPrevRel(long secondPrevRel);
	long getSecondNextRel() const;
	void setSecondNextRel(long secondNextRel);
	bool isFirstInFirstChain() const;
	void setFirstInFirstChain(bool firstInFirstChain);
	bool isFirstInSecondChain() const;
	void setFirstInSecondChain(bool firstInSecondChain);
	string toString();


private:
	long firstNode;
	long secondNode;
	int type;
	long firstPrevRel;
	long firstNextRel;
	long secondPrevRel;
	long secondNextRel;
	bool firstInFirstChain;
	bool firstInSecondChain;
};

