#include "RemovalsCountingDiffSets.h"



RemovalsCountingDiffSets::RemovalsCountingDiffSets()
{
}

RemovalsCountingDiffSets::RemovalsCountingDiffSets(set<long> addedElements, set<long> removedElements)
	:SuperDiffSets(addedElements, removedElements)
{
}


RemovalsCountingDiffSets::~RemovalsCountingDiffSets()
{
}

bool RemovalsCountingDiffSets::remove(long elem)
{
	// 如果已添加，则addedElements.remove
	// removedFromAdded 记录添加记录中的删除id（明确删除的纪录）
	// 如果没有添加，则放入删除记录Set中
	if (added(false).erase(elem))
	{
		removedFromAdded.insert(elem);
		return true;
	}
	pair<set<long>::iterator, bool> ret = removed(true).insert(elem);
	return ret.second;
}

bool RemovalsCountingDiffSets::wasRemoved(long id)
{
	return (!removedFromAdded.empty() && (removedFromAdded.find(id) != removedFromAdded.end())) || SuperDiffSets::isRemoved(id);
}
