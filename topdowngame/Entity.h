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
	Entity();
	~Entity();

	Hitbox h;

	TileMap* tileMap;

	double health;
	double maxHealth;

	double renderOrderOffset;
	
	bool removeMe;

	Animation* getCurrentAnimation();

	Entity(double x, double y, TileMap* tileMap);

	bool moveH(double dx, int tileId);
	bool moveV(double dy, int tileId);

	virtual void tick(double dt) = 0;

	virtual void render(sf::RenderWindow* window);

	void pushAnimation(Animation* a);

	virtual bool damage(double damage);

protected:
	std::vector<Animation*> animations;
	int animationIndex;
	sf::Sprite sprite;

	double healthBarOffsetX;
	double healthBarOffsetY;

	void setAnimationIndex(int index);
	void playCurrentAnimation(double dt);
};

