#pragma once

#include "ECS.h"
//#include "TransformComponent.h"
#include "Vector2D.h"
#include <iostream>
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;



class Player : public Entity
{
	int replayspeed = 50;
	//TransformComponent *transform;

public:
	bool isDead = false;
	vector<Vector2D> path;
	char ime[20];
	int score;
	Player(float x, float y, Manager &mManager, EntityType t);
	~Player();
	void moveAbsolute(int x, int y);
	void moveRelative(int x, int y);
	bool replay();
};

