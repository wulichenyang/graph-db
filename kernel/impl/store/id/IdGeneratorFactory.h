#pragma once
#include <map>
#include "IdType.h"
#include "IdGenerator.h"
#include "../../../../io/fs/FileChannel.h"
#include "../id/configuration/IdTypeConfigurationProvider.h"

using namespace std;
class IdGeneratorFactory
{
public:
	IdGeneratorFactory();
	IdGeneratorFactory(IdTypeConfigurationProvider idTypeConfigurationProvider);
	~IdGeneratorFactory();
	IdGenerator *open(FileChannel *filename, IdType idType, long highId, long maxId);
	IdGenerator *open(FileChannel *fileName, int grabSize, IdType idType, long highId, long maxId);
protected:
	IdGenerator *instantiate(FileChannel *fileName, int grabSize, long maxValue,
		bool aggressiveReuse, IdType idType, long highId);
private:
	// 将所有种类的id生成器用map保存，生成id时访问map，
	// 如果没有找到对应的id生成器，就打开文件并初始化，
	// 新的id生成器加入map中
	map<IdType, IdGenerator*> generators = map<IdType, IdGenerator*>();
	IdTypeConfigurationProvider idTypeConfigurationProvider;

	IdGenerator *get(IdType idType);
	void create(FileChannel *fileName, long highId, bool throwIfFileExists);
};

