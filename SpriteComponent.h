#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureMngr.h"
#include "Animation.h"
#include <map>

using namespace std;

class SpriteComponents : public Component {

private:

	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	map<const char*, Animation> animations;

	SpriteComponents() = default;

	SpriteComponents(const char *path) {
		setTex(path);
	}

	SpriteComponents(const char *path, bool isAnimated) {

		animated = isAnimated;
		Animation idle = Animation(0, 2, 300);
		Animation walk = Animation(1, 4, 300);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);


		Play("Idle");

		setTex(path);
	}

	~SpriteComponents() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char *path) {

		texture = TextureManager::LoadTexture(path);
	}
	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override {

		if (animated) {

			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

	void Play(const char* animName) {

		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};


