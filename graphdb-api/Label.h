#pragma once
#include <string>  

using namespace std;

class Label
{
public:
	Label(string str);
	~Label();
	string getName() const;
	string toString() const;

private:
	string name;
};

