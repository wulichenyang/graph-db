#pragma once
#include <map>

using namespace std;

template <class VALUE> 
class PrimitiveLongObjectMap
{
public:
	PrimitiveLongObjectMap();
	~PrimitiveLongObjectMap();

	VALUE put(long key, VALUE value);
	bool containsKey(long key);
	bool isEmpty();
	VALUE get(long key);
	VALUE remove(long key);
private:
	map<long, VALUE> l_v_map;
};
