#pragma once
class PropertyContainerState
{
public:
	PropertyContainerState();
	PropertyContainerState(long id);
	~PropertyContainerState();

	long getId();
	void clear();

private:
	long id;

	//private VersionedHashMap<int, Value> addedProperties;
	//private VersionedHashMap<int, Value> changedProperties;
	//private VersionedHashMap<int, Value> removedProperties;

}i

