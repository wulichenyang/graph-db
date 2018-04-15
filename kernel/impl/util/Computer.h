#pragma once
class Computer
{
public:
	Computer();
	~Computer();

	template <class T>
	const static int arrayLen(const T& array)const;
};
