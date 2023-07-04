#pragma once
#include "ECS.h"



class Garbage : public Entity
{
public:
	Garbage(float x, float y, Manager &mManager, EntityType t);
	~Garbage();
	void dvaupdate() override;
};

