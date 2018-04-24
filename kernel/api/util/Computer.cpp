#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

template<class T>
int Computer::arrayLen(const T & array)
{
	return (sizeof(array) / sizeof(array[0]));
}
