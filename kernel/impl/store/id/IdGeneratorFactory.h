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
	// �����������id��������map���棬����idʱ����map��
	// ���û���ҵ���Ӧ��id���������ʹ��ļ�����ʼ����
	// �µ�id����������map��
	map<IdType, IdGenerator*> generators = map<IdType, IdGenerator*>();
	IdTypeConfigurationProvider idTypeConfigurationProvider;

	IdGenerator *get(IdType idType);
	void create(FileChannel *fileName, long highId, bool throwIfFileExists);
};

