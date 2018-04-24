#pragma once
#include <set>
#include "../../../store/id/IdType.h"
#include "IdTypeConfiguration.h"
#include "../IdType.h"
#include <map>

using namespace std;

class IdTypeConfigurationProvider
{
public:
	IdTypeConfigurationProvider();
	~IdTypeConfigurationProvider();
	IdTypeConfiguration getIdTypeConfiguration(IdType idType);
	IdTypeConfiguration createIdTypeConfiguration(IdType idType);
protected:
	set<IdType> getTypesToReuse();
private:
	const set<IdType> TYPES_TO_ALLOW_REUSE = {
		IdType::PROPERTY, IdType::STRING_BLOCK,
		IdType::ARRAY_BLOCK, IdType::NODE_LABELS
	};
	map<IdType, IdTypeConfiguration> typeConfigurations;
};

