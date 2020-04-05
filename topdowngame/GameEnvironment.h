#pragma once

#include "Environment.h"
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "ResourceManager.h"

#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class GameEnvironment : public Environment
{
	
public:

	int counter;

	bool releasedR;

	map<string, bool> keys = {
		{"Move Up", false},
		{"Move Left", false},
		{"Move Down", false},
		{"Move Right", false} };

	vector<Entity*> entities;
	vector<Projectile> projectiles;

	Entity* focusEntity;

	TileMap tileMap;
	vector<vector<int>> mapDefinition;

	void tick();
	void render();

	void eventHandler(sf::Event& event);

	vector<vector<int>>& generateMap();
	sf::Texture* getTileset();

	GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment);
	~GameEnvironment();

	void tickProjectiles();
	void summonProjectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y, sf::Texture* tex);
};

