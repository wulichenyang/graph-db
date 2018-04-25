#pragma once
#include <map>

using namespace std;

template <class VALUE> 
class PrimitiveIntObjectMap
{
public:
	PrimitiveIntObjectMap();
	~PrimitiveIntObjectMap();

	VALUE put(int key, VALUE value);
	bool containsKey(int key);
	VALUE get(int key);
	VALUE remove(int key);

private:
	map<int, VALUE> i_v_map;
};

