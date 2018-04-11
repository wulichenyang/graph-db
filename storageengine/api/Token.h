#pragma once
#include <string> 

using namespace std;

class Token
{
public:
	Token(string name, int id);
	~Token();
	string getName() const;
	int getId() const;

private:
	string name;
	int id;
};

