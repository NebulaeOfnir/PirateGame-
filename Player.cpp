#include "Player.h"
#include "Components.h"
#include "TransformComponent.h"
#include <string>
#define _CRT_SECURE_NO_WARNINGS


Player::Player(float x, float y, Manager &mManager, EntityType t) :Entity(mManager, t)
{
	std::string temp;
	cout << "Input name:" << endl;
	getline(cin, temp);
	strcpy_s(ime, temp.c_str());
	cout << ime << endl;
	score = 0;
	addComponent<TransformComponent>(x, y, 32, 32, 1);
	//transform = &getComponent<TransformComponent>();
	addComponent<SpriteComponents>("Assets/EnemyChar.png");
	addComponent<KeyboardController>();
	addComponent<ColliderComponent>("Player");
	addComponent<NewCollisionComponent>();
	path.push_back(Vector2D(x, y));
}

/*int Player::getScore()
{
	return score;
}

void Player::addScore(int y)
{
	score += y;
}*/
Player::~Player()
{
}

void Player::moveAbsolute(int x, int y)
{
	static TransformComponent *transform = &getComponent<TransformComponent>();
	transform->position.x = x;
	transform->position.y = y;

}

void Player::moveRelative(int x, int y)
{
	static TransformComponent *transform = &getComponent<TransformComponent>();
	if (!isDead)
	{
		transform->position.x += x;
		transform->position.y += y;
	}
}

bool Player::replay()
{
	isDead = true; // temp

	static std::chrono::steady_clock::time_point start = Clock::now();

	static int index = 0;

	auto t2 = Clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start).count() > replayspeed) {

		if(!(index<path.size()))
			return false;

		moveAbsolute(path[index].x, path[index].y);

		index++;

		start = t2;
	}
	return true;

}
