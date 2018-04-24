#include "IdTypeConfigurationProvider.h"



IdTypeConfigurationProvider::IdTypeConfigurationProvider()
{
}


IdTypeConfigurationProvider::~IdTypeConfigurationProvider()
{
}

IdTypeConfiguration IdTypeConfigurationProvider::getIdTypeConfiguration(IdType idType)
{
	map<IdType, IdTypeConfiguration>::iterator iter = typeConfigurations.find(idType);
	if (iter != typeConfigurations.end())
	{
		return iter->second;
	}
	return createIdTypeConfiguration(idType);
}

IdTypeConfiguration IdTypeConfigurationProvider::createIdTypeConfiguration(IdType idType)
{
	bool flag = (getTypesToReuse().find(idType)) != (getTypesToReuse().end());
	IdTypeConfiguration conf = IdTypeConfiguration(flag);
	typeConfigurations[idType] = conf;
	return conf;
}

set<IdType> IdTypeConfigurationProvider::getTypesToReuse()
{
	return TYPES_TO_ALLOW_REUSE;
}
