#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

template<class T>
inline const int Computer::arrayLen(const T & array) const
{
	return (sizeof(array) / sizeof(array[0]));
}
