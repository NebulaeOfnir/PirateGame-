#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponents.h"
#include "Collision.h"

using namespace std;


class DestroyKillComponent : public Component
{
	TransformComponent *transform;
	//std::unique_ptr<Entity> cComp, oComp;
	Collision col;
	Manager *manager;


public:

	DestroyKillComponent(Manager& m)
	{ 
		//*manager = m; 
	}


	void init() override
	{
		
		transform = &entity->getComponent<TransformComponent>();
	}
	void update() override
	{
		/*
		std::vector<std::unique_ptr<Entity>>& entities = manager->GetEntities();
		for (int i = 0; i < entities.size(); i++) {
			auto cComp = &entities[i]->getComponent<ColliderComponent>();
			for (int j = i + 1; j < entities.size(); j++) {
				auto oComp = &entities[j]->getComponent<ColliderComponent>();
				//col.AABB(i, j);
			}
		}
		*/
	}
};