#pragma once
#include <map>
#include "IdType.h"
#include "IdGenerator.h"
#include "../../../../io/fs/FileChannel.h"

using namespace std;
class IdGeneratorFactory
{
public:
	IdGeneratorFactory();
	~IdGeneratorFactory();

private:
	map<IdType, IdGenerator> *generators = new map<IdType, IdGenerator>();
	FileChannel * file;
};

