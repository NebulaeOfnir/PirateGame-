#include "Enemy.h"
#include "Components.h"
#include "KillComponent.h"



Enemy::Enemy(float x, float y, Manager & mManager, EntityType t):Entity(mManager, t)
{

	addComponent<TransformComponent>(x, y, 32, 32, 1);
	addComponent<SpriteComponents>("Assets/Enemy2Char.png", false);
	addComponent<ColliderComponent>("Enemy");
	addComponent<EnemyComponent>(1);
	addComponent<NewCollisionComponent>();
	//addComponent<KillComponent>();

}

Enemy::~Enemy()
{
}
