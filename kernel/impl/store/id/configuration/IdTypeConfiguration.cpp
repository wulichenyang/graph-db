#include "IdTypeConfiguration.h"



IdTypeConfiguration::IdTypeConfiguration()
{
}

IdTypeConfiguration::IdTypeConfiguration(bool allowAggressiveReuse)
{
	this->allowAggressiveReuse = allowAggressiveReuse;
}


IdTypeConfiguration::~IdTypeConfiguration()
{
}

bool IdTypeConfiguration::ifAllowAggressiveReuse()
{
	return allowAggressiveReuse;
}

int IdTypeConfiguration::getGrabSize()
{
	return allowAggressiveReuse ? AGGRESSIVE_GRAB_SIZE : DEFAULT_GRAB_SIZE;
}
