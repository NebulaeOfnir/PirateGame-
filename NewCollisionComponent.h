#pragma once


#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"


using namespace std;



class NewCollisionComponent : public Component
{
	TransformComponent *transform, *tmp;
	bool isPlayer = false;
	//Entity *ent;
	
	
public:
	bool IsColliding = false;
	static Vector2D pospos;
	EntityType tip;
	static int *score;
	
	/*NewCollisionComponent(Entity *entity)
	{

	}
*/

	void init() override
	{
		tip = entity->getType();
		transform = &entity->getComponent<TransformComponent>();

		if (tip == EntityType::PLAYER) {
			Player *player = (Player*)entity;
			score = &player->score;
			isPlayer = true;
			pospos.x = transform->tilepos.x*32;
			pospos.y = transform->tilepos.y*32;
		}
		

	}
	void update() override
	{
		
		if (!isPlayer)
		{
			if (Game::numEnemiesAt(pospos.x, pospos.y) > 1)
			{
				Player *player = (Player*)entity;
				player->isDead = true;
			}
			if (pospos.x == transform->tilepos.x*32 && pospos.y == transform->tilepos.y*32)
			{
				IsColliding = true;
				if (tip == EntityType::ENEMY)
				{
					*score += 5;
				}
				else if (tip == EntityType::GARBAGE)
				{
					*score += 10;
				}
				entity->destroy();

			}
		}
		else
		{
			pospos.x = transform->tilepos.x*32;
			pospos.y = transform->tilepos.y*32;
			if (Game::numEnemiesAt(pospos.x, pospos.y) > 1)
			{
				Player *player = (Player*)entity;
				player->isDead = true;
				
			}
		}
		
		
	}
	

};
