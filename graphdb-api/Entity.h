#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual long getId() const = 0;
};

