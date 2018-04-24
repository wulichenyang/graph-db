#pragma once

template <class VALUE> class PrimitiveLongObjectMap
{
public:
	PrimitiveLongObjectMap();
	~PrimitiveLongObjectMap();
	VALUE put(long key, VALUE value);
	bool containsKey(long key);
	VALUE get(long key);
	VALUE remove(long key);
};
