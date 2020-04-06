#pragma once

#include "Environment.h"
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Item.h"

#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class GameEnvironment : public Environment
{
	
public:

	bool releasedR;

	map<string, bool> keys = {
		{"Move Up", false},
		{"Move Left", false},
		{"Move Down", false},
		{"Move Right", false},
		{"Left Click", false}
	};

	vector<Entity*> entities;
	vector<Projectile*> projectiles;

	Entity* focusEntity;

	TileMap tileMap;
	vector<vector<int>> mapDefinition;

	void tick(double dt);
	void render();

	void eventHandler(sf::Event& event);

	vector<vector<int>>& generateMap();
	sf::Texture* getTileset();

	GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave);
	~GameEnvironment();

	void tickProjectiles(double dt);
	void summonProjectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y);
	void deleteProjectile(int index);
};

