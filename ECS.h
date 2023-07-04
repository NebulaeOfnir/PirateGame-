#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <chrono>
#include "Vector2D.h"


using namespace std;

class Component;

class Entity;

class Manager;

using ComponentID = size_t;

using Group = size_t;

typedef std::chrono::high_resolution_clock Clock;


inline ComponentID getNewComponentTypeID() {

	static ComponentID lastID = 0u;
	return lastID++;

}


template <typename T> inline ComponentID getComponentTypeID() noexcept {

	static ComponentID typeID = getNewComponentTypeID();
	return typeID;

}

enum class EntityType
{
	PLAYER,
	ENEMY,
	GARBAGE,
	ALLY
};

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

using ComponentBitSet = bitset<maxComponents>;
using GroupBitSet = bitset<maxGroups>;

using ComponentArray = array<Component *, maxComponents>;

class Component {

public:

	Entity *entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

};

class Entity {

protected:

	EntityType type;

	Manager& manager;

	bool active = true;
	vector<unique_ptr<Component>> components;

	ComponentBitSet componentBitSet;
	ComponentArray componentArray;
	GroupBitSet groupBitSet;
	//TransformComponent transform;
public:

	Manager &getManager()
	{
		return manager;
	}

	/*Entity (float x, float y, Manager &mManager):manager(mManager)
	{
		addComponent<TransformComponent>(2);
		TransformComponent* transform = &getComponent<TransformComponent>();
		transform->position.x = x;
		transform->position.y = y;

	}*/

	virtual void dvaupdate(){}


	Entity(Manager &mManager, EntityType t) : manager(mManager), type(t) {

	}

	void update() {

		for (auto &c : components) c->update();
	}


	void draw() {

		for (auto &c : components) c->draw();
	}

	bool isActive() const { return active; }

	void destroy() { active = false; }

	bool hasGroup(Group mGroup) {

		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup) {

		groupBitSet[mGroup] = false;
	}

	EntityType getType()
	{
		return type;
	}

	template <typename T> bool hasComponent() const {

		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T &addComponent(TArgs&&... mArgs) {

		T *c(new T(forward<TArgs>(mArgs)...));
		c->entity = this;
		unique_ptr<Component> uPtr{ c };
		components.emplace_back(move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();

		return *c;
	}

	template <typename T> T& getComponent() const {

		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);

	}

};

class Manager {

	int duration = 500;
	std::chrono::steady_clock::time_point start;

	vector<unique_ptr<Entity>> entities;
	array<vector<Entity*>, maxGroups> groupedEntities;
	
public:

	/*int numEnemiesAt(int x, int y)
	{
		int temp = 0;
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->getType() == EntityType::ENEMY && entities[i]->getComponent<TransformComponent>().position.x == x && entities[i]->getComponent<TransformComponent>().position.y == y)
			{
				temp++;
			}
		}
		return temp;
	}
	*/
	void update() {

		//auto t2 = Clock::now();
		for (auto &e : entities) e->update();
		/*if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start).count() > duration) {

			for (auto &e : entities) e->dvaupdate();
			start = t2; // Clock::now;
		}
		*/
	}

	void Draw() {
		for (auto &e : entities)e->draw();
	}

	void refresh() {

		for (auto i(0u); i < maxGroups; i++) {

			auto& v(groupedEntities[i]);
			v.erase(

				remove_if(begin(v), end(v),
					[i](Entity* mEntity) {

				return !mEntity->isActive() || !mEntity->hasGroup(i);

			}

				),
				end(v));
		}

		entities.erase(remove_if(begin(entities), end(entities), [](const unique_ptr<Entity> &mEntity) {

			return !mEntity->isActive();

		}

		),
			end(entities));
	}


	void AddToGroup(Entity* mEntity, Group mGroup) {

		groupedEntities[mGroup].emplace_back(mEntity);

	}

	vector<Entity*>& getGroup(Group mGroup) {

		return groupedEntities[mGroup];

	}

	/*Entity &addEntity() {

		Entity *e = new Entity(*this, type);

		unique_ptr<Entity> uPtr{ e };

		entities.emplace_back(move(uPtr));

		return *e;
	}*/

	void addEntity(Entity *e)
	{
		unique_ptr<Entity> uPtr{ e };

		entities.emplace_back(move(uPtr));

		//std::cout << e << " " << entities.size() << endl;
	}

	vector<unique_ptr<Entity>> &GetEntities()
	{
		return entities;
	}

};