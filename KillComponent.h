#pragma once

#include "Game.h"
#include "Components.h"
#include "Vector2D.h"


using namespace std;

class KillComponent :public Component
{

	NewCollisionComponent *newcollide;

public:
	
	void init() override 
	{
		newcollide = &entity->getComponent<NewCollisionComponent>();
	}

	void update() override 
	{

		if (newcollide->IsColliding)
		{
			entity->destroy();
		}


	}
	
};
