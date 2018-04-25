#include "PropertyContainerState.h"



PropertyContainerState::PropertyContainerState()
{
}

PropertyContainerState::PropertyContainerState(long id)
{
	this->id = id;
}


PropertyContainerState::~PropertyContainerState()
{
}

long PropertyContainerState::getId()
{
	return id;
}
