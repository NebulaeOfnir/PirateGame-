#include "Garbage.h"
#include "Components.h"
#include "KillComponent.h"




Garbage::Garbage(float x, float y, Manager &mManager, EntityType t):Entity(mManager, t)
{
	addComponent<TransformComponent>(x, y, 24, 32, 1);
	addComponent<SpriteComponents>("Assets/Boi.png", false);
	addComponent<ColliderComponent>("Trash");
	addComponent<EnemyComponent>(2);
	addComponent<NewCollisionComponent>();
	//addComponent<KillComponent>();
}


Garbage::~Garbage()
{
}

void Garbage::dvaupdate()
{


}