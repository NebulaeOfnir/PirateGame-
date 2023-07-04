#pragma once

#include "Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "Components.h"
#include "SpriteComponent.h"
#include "Vector2D.h"
#include "Playerpos.h"



using namespace std;



class KeyboardController : public Component {
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


	bool IsOnWater;


public:
	Playerpos play;
	TransformComponent *transform;
	SpriteComponents *sprite;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponents>();

	}

	void changetile()
	{
		int x, y, output;
		x = transform->tilepos.x;
		y = transform->tilepos.y;
		output = lvl1[y][x];
		if (output > 0)
		{
			IsOnWater = 0;
		}
		else
		{
			IsOnWater = 1;
		}

	}

	bool nexttile(int nxt, bool inxpos)
	{
		int x, y, output, output2;
		x = transform->tilepos.x;
		y = transform->tilepos.y;
		output = lvl1[y][x];
		if (inxpos)
			x += nxt;
		else
			y += nxt;
		output2 = lvl1[y][x];

		IsOnWater = output;

		if (output == output2)
		{
			return false;
		}
		else
		{
			return true;
		}

	}

	void boatornoat(int i, bool y)
	{
		if (nexttile(i, y))
		{
			if (IsOnWater == false)
			{
				sprite->setTex("Assets/EnemyChar.png");
			}
			else
			{
				sprite->setTex("Assets/Boat.png");
			}
		}
	}


	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			Player* p = (Player*)entity;
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				boatornoat(-1, 0);
				//transform->position.y += -32;
				p->moveRelative(0, -32);
				p->path.push_back(transform->position);
				//sprite->Play("Walk");
				break;
			case SDLK_a:
				boatornoat(-1, 1);
				p->moveRelative(-32, 0);
				//transform->position.x += -32;
				p->path.push_back(transform->position);
				//sprite->Play("Walk");
				break;
			case SDLK_s:
				boatornoat(1, 0);
				p->moveRelative(0, 32);
				//transform->position.y += 32;
				p->path.push_back(transform->position);
				//sprite->Play("Walk");
				break;
			case SDLK_d:
				boatornoat(1, 1);
				p->moveRelative(32, 0);
				//transform->position.x += 32;
				p->path.push_back(transform->position);
				//sprite->Play("Walk");
				break;
			case SDLK_f:
				p->isDead = true;
				break;

			default:
				break;
			}
			/*cout << "----------" << endl;
			for (int i = 0; i < p->path.size(); i++)
				cout << p->path[i].x << " " << p->path[i].y << endl;*/
		}

		else if (Game::event.type == SDL_KEYUP) {

			switch (Game::event.key.keysym.sym)
			{

			case SDLK_w:
				//transform->position.y = 0;
				//sprite->Play("Walk");
				break;

			case SDLK_a:
				//transform->position.x = 0;
				//sprite->Play("Walk");
				break;

			case SDLK_s:
				//transform->position.y = 0;
				//sprite->Play("Walk");
				break;

			case SDLK_d:
				//transform->position.x = 0;
				//sprite->Play("Walk");
				break;

			default:
				break;
			}
		}

	}
};

