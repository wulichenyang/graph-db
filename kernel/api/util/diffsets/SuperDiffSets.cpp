#include "SuperDiffSets.h"


template<class T>
inline SuperDiffSets<T>::SuperDiffSets()
{
}

template<class T>
inline SuperDiffSets<T>::SuperDiffSets(set<T> added, set<T> removed)
{
	this->addedElements = added;
	this->removedElements = removed;
}

template<class T>
inline SuperDiffSets<T>::~SuperDiffSets()
{
}

template<class T>
bool SuperDiffSets<T>::add(T elem)
{
	bool wasRemoved = removed(false).erase(elem);
	// Add to the addedElements only if it was not removed from the removedElements
	
	wasRemoved || pair<set<T>::iterator, bool> ret = added(true).insert(elem);
	return wasRemoved || ret.second;
}

template<class T>
void SuperDiffSets<T>::replace(T toRemove, T toAdd)
{
	set<T> added = added(true); // we're doing both add and remove on it, so pass in true
	bool removedFromAdded = added.erase(toRemove);
	removed(false).erase(toAdd);

	added.insert(toAdd);
	if (!removedFromAdded)
	{
		removed(true).insert(toRemove);
	}
}

template<class T>
bool SuperDiffSets<T>::remove(T elem)
{
	bool removedFromAddedElements = added(false).erase(elem);
	// Add to the removedElements only if it was not removed from the addedElements.
	removedFromAddedElements || pair<set<T>::iterator, bool> ret = removed(true).insert(elem);
	return removedFromAddedElements || ret.second;
}

template<class T>
void SuperDiffSets<T>::addAll(vector<T> elems)
{
	size_t length = elems.size();
	for (size_t i = 0; i < length; i++)
	{
		add(elems[i]);
	}
}

template<class T>
void SuperDiffSets<T>::removeAll(vector<T> elems)
{
	size_t length = elems.size();
	for (size_t i = 0; i < length; i++)
	{
		remove(elems[i]);
	}
}

template<class T>
bool SuperDiffSets<T>::isAdded(T elem)
{
	set<T> s = added(false);
	return s.find(elem) != s.end();
}

template<class T>
inline bool SuperDiffSets<T>::isRemoved(T elem)
{
	set<T> s = removed(false);
	return s.find(elem) != s.end();
}

template<class T>
inline set<T> SuperDiffSets<T>::getAdded()
{
	return addedElements;
}

template<class T>
inline set<T> SuperDiffSets<T>::getAddedSnapshot()
{
	return addedElements;
}

template<class T>
inline set<T> SuperDiffSets<T>::getRemoved()
{
	return removedElements;
}

template<class T>
inline bool SuperDiffSets<T>::isEmpty()
{
    return added( false ).empty() && removed( false ).empty();
}

//template<class T>
//inline vector<T> SuperDiffSets<T>::apply(vector<T> source)
//{
//	vector<T> result = source;
//	if ((!removedElements.empty() && !removedElements.empty()) ||
//		(!addedElements.empty() && !addedElements.empty()))
//	{
//		ensureFilterHasBeenCreated();
//		result = vector.filter(filter, result);
//	}
//	if (!addedElements.empty() && !addedElements.empty())
//	{
//		result = vector.concat(result, addedElements.iterator());
//	}
//	return result;
//}

template<class T>
inline set<T> SuperDiffSets<T>::added(bool create)
{
	return addedElements;
}

template<class T>
inline set<T> SuperDiffSets<T>::removed(bool create)
{
	return removedElements;
}

template<class T>
inline int SuperDiffSets<T>::delta()
{
	return added(false).size() - removed(false).size();
}

template<class T>
inline bool SuperDiffSets<T>::unRemove(T item)
{
	return removed(false).erase(item);
}

template<class T>
inline void SuperDiffSets<T>::clear()
{
	if (!addedElements.empty() )
	{
		addedElements.clear();
	}
	if (!removedElements.empty())
	{
		removedElements.clear();
	}
}

template<class T>
inline string SuperDiffSets<T>::toString()
{
	return "added( false ), removed( false )";
}
