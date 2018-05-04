#pragma once
#include "CommonAbstractStore.h"
#include "record\NodeRecord.h"

class NodeStore:public CommonAbstractStore<NodeRecord>
{
public:
	NodeStore();
	~NodeStore();
};

