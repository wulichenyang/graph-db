#pragma once
#include "IdGenerator.h"
#include "IdContainer.h"
#include "IdType.h"

class IdGeneratorImpl :IdGenerator
{
public:
	const static long INTEGER_MINUS_ONE = 0xFFFFFFFFL;

	IdGeneratorImpl();
	~IdGeneratorImpl();

private:
	const long max;
	const IdContainer idContainer;
	long highId;
	const IdType idType;
};

