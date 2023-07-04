#pragma once

#include "Game.h"
#include "Components.h"
#include "Vector2D.h"
#include <fstream>

using namespace std;

struct dingdong
{
	int x, y;
};


class TransformComponent : public Component {
public:

	Vector2D position;
	Vector2D velocity;
	Vector2D tilepos;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() 
	{
		position.Zero();
	}

	TransformComponent(int sc) 
	{
		position.Zero();
		scale = sc;
	}


	TransformComponent(float x, float y, int h, int w, int sc) {
		tilepos.x = x / 32;
		tilepos.y = y / 32;
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}

	void save()
	{
		struct dingdong ding;
		ofstream data;
		data.open("Quicksave.bin", ios::binary | ios::app);
		ding.x = position.x;
		ding.y = position.y;
		if (data.is_open())
		{
			data.write((char*)&ding, sizeof(ding));
			data.close();

		}


	}

	void update() override {

		tilepos.x = position.x / 32;
		tilepos.y = position.y / 32;
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		if (tilepos.x > 24)
			position.x = 24 * 32;
		else if (tilepos.x < 0)
			position.x = 0;
		if (tilepos.y > 19)
			position.y = 19 * 32;
		else if (tilepos.y < 0)
			position.y = 0;
		if (Game::event.type == SDL_KEYDOWN) {

			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				save();
				Game::isRunning = false;
			default:
				break;
			}


		}
	}
};
