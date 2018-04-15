#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

template<class T>
static int Computer::arrayLen(const T & array)
{
	return (sizeof(array) / sizeof(array[0]));
}
