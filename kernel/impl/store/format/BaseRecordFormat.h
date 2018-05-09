#pragma once
class BaseRecordFormat
{
public:
	BaseRecordFormat();
	~BaseRecordFormat();
	const static long longFromIntAndMod(long base, long modifier);
};

