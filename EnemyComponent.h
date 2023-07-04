#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
//#include "Map.h"
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

class EnemyComponent : public Component
{
	int lvl1[20][25] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};


	int typeofchar;
	int duration = 800;
	int randomMove;
public:
	TransformComponent *transform;
	std::chrono::steady_clock::time_point start;


	EnemyComponent(int tip)
	{
		typeofchar = tip;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	int currtile()
	{
		int x, y, output;
		x = transform->tilepos.x;
		y = transform->tilepos.y;
		output = lvl1[y][x];
		return output;
		
	}

	int nexttile(int nxt, bool inxpos)
	{
		int x, y, output;
		x = transform->tilepos.x;
		y = transform->tilepos.y;
		if (inxpos)
		{
			x += nxt;
		}
		else
		{
			y += nxt;
		}

		output = lvl1[y][x];
		return output;

	}

	void update() override
	{
		auto t2 = Clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start).count() > duration) {

			randomMove = rand() % 4 + 1;
			switch (typeofchar)
			{

			case 1:
				switch (randomMove)
				{
				case 1:
					if(nexttile(-1, 0) > 0)
					transform->position.y += -32;
					//sprite->Play("Walk");
					break;
				case 2:
					if (nexttile(-1, 1) > 0)
					transform->position.x += -32;
					//sprite->Play("Walk");
					break;
				case 3:
					if (nexttile(1, 0) > 0)
					transform->position.y += 32;
					//sprite->Play("Walk");
					break;
				case 4:
					if (nexttile(1, 1) > 0)
					transform->position.x += 32;
					//sprite->Play("Walk");
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (randomMove)
				{
				case 1:
					if (nexttile(-1, 0) == 0)
					transform->position.y += -32;
					//sprite->Play("Walk");
					break;
				case 2:
					if (nexttile(-1, 1) == 0)
					transform->position.x += -32;
					//sprite->Play("Walk");
					break;
				case 3:
					if (nexttile(1, 0) == 0)
					transform->position.y += 32;
					//sprite->Play("Walk");
					break;
				case 4:
					if (nexttile(1, 1) == 0)
					transform->position.x += 32;
					//sprite->Play("Walk");
					break;
				default:
					break;
				}
				break;
			}
			start = t2; // Clock::now;
		}

		
		

	}



};
