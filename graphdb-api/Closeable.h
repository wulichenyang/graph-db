#pragma once
class Closeable
{
public:
	Closeable();
	~Closeable();
	virtual void close() = 0;
};

