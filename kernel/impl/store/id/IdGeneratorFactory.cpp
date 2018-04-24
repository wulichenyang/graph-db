#include "IdGeneratorFactory.h"



IdGeneratorFactory::IdGeneratorFactory()
{
	IdGeneratorFactory(IdTypeConfigurationProvider());
}

IdGeneratorFactory::IdGeneratorFactory(IdTypeConfigurationProvider idTypeConfigurationProvider)
{
	this->idTypeConfigurationProvider = idTypeConfigurationProvider;
}


IdGeneratorFactory::~IdGeneratorFactory()
{
	map<IdType, IdGenerator*>::iterator iter = generators.begin();

	for (; iter != generators.end(); iter++)
	{
		delete (iter->second);
	}
}

IdGenerator * IdGeneratorFactory::open(FileChannel * filename, IdType idType, LongSupplier * highId, long maxId)
{
	IdTypeConfiguration idTypeConfiguration = idTypeConfigurationProvider.getIdTypeConfiguration(idType);
	return open(filename, idTypeConfiguration.getGrabSize(), idType, highId, maxId);

}

IdGenerator * IdGeneratorFactory::open(FileChannel * fileName, int grabSize, IdType idType, LongSupplier * highId, long maxId)
{
	IdTypeConfiguration idTypeConfiguration = idTypeConfigurationProvider.getIdTypeConfiguration(idType);
	IdGenerator *generator = instantiate(fileName, grabSize, maxId, idTypeConfiguration.ifAllowAggressiveReuse(),
		idType, highId);
	generators[idType] = generator;
	return generator;
}

IdGenerator * IdGeneratorFactory::instantiate(FileChannel * fileName, int grabSize, long maxValue, bool aggressiveReuse, IdType idType, LongSupplier * highId)
{
	return new IdGenerator(fileName, grabSize, maxValue, aggressiveReuse, idType, highId);
}

IdGenerator * IdGeneratorFactory::get(IdType idType)
{
	map<IdType, IdGenerator*>::iterator iter = generators.find(idType);
	if (iter != generators.end())
	{
		return generators[idType];
	}
	return NULL;
}

void IdGeneratorFactory::create(FileChannel * fileName, long highId, bool throwIfFileExists)
{
	IdGenerator::createGenerator(fileName, highId, throwIfFileExists);
}
