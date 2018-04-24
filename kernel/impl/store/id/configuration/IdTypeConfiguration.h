#pragma once
class IdTypeConfiguration
{
public:
	const static int DEFAULT_GRAB_SIZE = 1024;
	const static int AGGRESSIVE_GRAB_SIZE = 50000;
	int getGrabSize();
	bool ifAllowAggressiveReuse();

	IdTypeConfiguration();
	IdTypeConfiguration(bool allowAggressiveReuse);
	~IdTypeConfiguration();
private:
	bool allowAggressiveReuse;
};

