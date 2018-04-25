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
	// �������ӣ���addedElements.remove
	// removedFromAdded ��¼��Ӽ�¼�е�ɾ��id����ȷɾ���ļ�¼��
	// ���û����ӣ������ɾ����¼Set��
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
