#pragma once
#include "../util/diffsets/SuperDiffSets.h"

class RemovalsCountingDiffSets :public SuperDiffSets<long>
{
public:
	RemovalsCountingDiffSets();
	RemovalsCountingDiffSets(set<long> addedElements, set<long> removedElements);
	~RemovalsCountingDiffSets();
	bool remove(long elem);
	bool wasRemoved(long id);

private:
	set<long> removedFromAdded;


};

