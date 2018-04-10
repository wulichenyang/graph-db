#pragma once
#include <string> 

using namespace std;

class RelationshipType
{
public:
	RelationshipType(string str);
	~RelationshipType();
	string getName() const;
	string toString() const;

private:
	string name;
};

