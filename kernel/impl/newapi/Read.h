#pragma once
#include "../../api/KernelTransaction.h"

class Read
{
public:
	Read();
	Read(KernelTransaction *ktx);
	~Read();

	KernelTransaction *ktx;

};

