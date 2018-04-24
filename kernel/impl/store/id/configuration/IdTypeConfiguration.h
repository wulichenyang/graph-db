#pragma once
class IdTypeConfiguration
{
public:
	const static int DEFAULT_GRAB_SIZE = 1024;
	const static int AGGRESSIVE_GRAB_SIZE = 50000;

	IdTypeConfiguration();
	IdTypeConfiguration(bool allowAggressiveReuse);
	~IdTypeConfiguration();
private:
	bool allowAggressiveReuse;
	bool ifAllowAggressiveReuse();
	int getGrabSize();
};

