#pragma once

#include "Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "Components.h"
#include "SpriteComponent.h"

using namespace std;

class EnemyCollision : public Component
{
	TransformComponent *transform;
public:

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{

	}


};