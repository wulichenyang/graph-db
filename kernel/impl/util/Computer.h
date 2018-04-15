#pragma once
class Computer
{
public:
	Computer();
	~Computer();

	template <class T>
	static int arrayLen(const T& array);
};
