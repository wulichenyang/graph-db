#include "PrimitiveLongObjectMap.h"



template<class VALUE>
inline PrimitiveLongObjectMap<VALUE>::PrimitiveLongObjectMap()
{
}

template<class VALUE>
inline PrimitiveLongObjectMap<VALUE>::~PrimitiveLongObjectMap()
{
}

template<class VALUE>
inline VALUE PrimitiveLongObjectMap<VALUE>::put(long key, VALUE value)
{
	l_v_map[key] = value;
	return value;
}

template<class VALUE>
inline bool PrimitiveLongObjectMap<VALUE>::containsKey(long key)
{
	return (l_v_map.find(key) != l_v_map.end());
}

template<class VALUE>
bool PrimitiveLongObjectMap<VALUE>::isEmpty()
{
	return this->l_v_map.empty();
}

template<class VALUE>
inline VALUE PrimitiveLongObjectMap<VALUE>::get(long key)
{
	return l_v_map[key];
}

template<class VALUE>
inline VALUE PrimitiveLongObjectMap<VALUE>::remove(long key)
{
	VALUE value = get(key);
	l_v_map.erase(key);
	return value;
}

