#pragma once
#include <set>
#include "../../../../storageengine/api/txstate/DiffSetsVisitor.h"
#include <vector>
#include <string>

using namespace std;

template <class T>
class SuperDiffSets
{
public:
	SuperDiffSets();
	SuperDiffSets(set<T> added, set<T> removed);
	~SuperDiffSets();
	//accept(DiffSetsVisitor<T> visitor);
	bool add(T elem);
	void replace(T toRemove, T toAdd);
	virtual bool remove(T elem);
	void addAll(vector<T> elems);
	void removeAll(vector<T> elems);
	bool isAdded(T elem);
	bool isRemoved(T elem);
	set<T> getAdded();
	set<T> getAddedSnapshot();
	set<T> getRemoved();
	bool isEmpty();
	//vector<T> apply(vector<T> source);
protected:
	set<T> added(bool create);
	set<T> removed(bool create);
	int delta();
	bool unRemove(T item);
	void clear();
	string toString();

private:
	set<T> addedElements;
	set<T> removedElements;

};