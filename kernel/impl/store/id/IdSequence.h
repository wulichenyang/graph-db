#pragma once
class IdSequence
{
public:
	IdSequence();
	~IdSequence();
	virtual long nextId() = 0;
};

