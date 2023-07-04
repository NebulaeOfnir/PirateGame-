#pragma once
#include "ECS.h"


class Enemy:public Entity
{
public:
	Enemy(float x, float y, Manager &mManager, EntityType t);
	~Enemy();
};

