#pragma once
#include <string> 

using namespace std;

class Token
{
public:
	Token();
	~Token();

private:
	const static string name;
	const static int id;
};

