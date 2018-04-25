#include "PrimitiveIntObjectMap.h"


template<class VALUE>
PrimitiveIntObjectMap::PrimitiveIntObjectMap()
{
}

template<class VALUE>
PrimitiveIntObjectMap::~PrimitiveIntObjectMap()
{
}

template<class VALUE>
VALUE PrimitiveIntObjectMap<VALUE>::put(int key, VALUE value)
{
	i_v_map[key] = value;
	return value;
}

template<class VALUE>
bool PrimitiveIntObjectMap<VALUE>::containsKey(int key)
{
	return (i_v_map.find(key) != i_v_map.end());
}

template<class VALUE>
VALUE PrimitiveIntObjectMap<VALUE>::get(int key)
{
	return i_v_map[key];
}

template<class VALUE>
VALUE PrimitiveIntObjectMap<VALUE>::remove(int key)
{
	VALUE value = get(key);
	i_v_map.erase(key);
	return value;
}
