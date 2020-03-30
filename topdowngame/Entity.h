#pragma once

#include "Hitbox.h"

#include <SFML/Graphics.hpp>

#include "Animation.h"

#include "TileMap.h"

#include "ResourceManager.h"

#include <vector>

using namespace std;

class Entity
{

public:

	~Entity() = default;

	Hitbox h;

	TileMap* tileMap;

	vector<Entity*>* entityList;

	ResourceManager* resourceManager;

	double health;
	double maxHealth;
	
	Entity(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager);

	bool moveH();
	bool moveV();

	virtual void tick() = 0;

	void render(sf::RenderWindow* window);

	void pushAnimation(Animation a);

protected:
	std::vector<Animation> animations;
	int animationIndex;
	sf::Sprite sprite;

	Animation getCurrentAnimation();
	void setAnimationIndex(int index);
	void playCurrentAnimation();
};

