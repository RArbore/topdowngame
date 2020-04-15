#pragma once

#include "Environment.h"
#include "Entity.h"
#include "Player.h"
#include "Slime.h"
#include "Mushroom.h"
#include "Zombie.h"
#include "Minotaur.h"
#include "MagicRock.h"
#include "BossMagicRock.h"
#include "Projectile.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "WorldGenerator.h"
#include "Item.h"

#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <atomic>
#include <thread>

using namespace std;

class Player;
class Particle;
class JungleTree;

class GameEnvironment : public Environment
{
	
public:

	const static int WORLD_CELLS_COUNT = 25; // number of regions/cells
	const static int WORLD_MAP_SIZE = 1000; // size of the generated map
	const static int WORLD_MAP_SCALE = 1; // how much to scale the generated map

	bool releasedR;

	map<string, bool> keys = {
		{"Move Up", false},
		{"Move Left", false},
		{"Move Down", false},
		{"Move Right", false},
		{"Left Click", false}
	};

	map<int, vector<Entity*>> entities; // map region -> entity list
	vector<Projectile*> projectiles;
	vector<Particle*> visuals;

	Entity* focusEntity;
	Player* player;

	WorldGenerator worldGenerator;
	TileMap tileMap;

	thread changeRegionThread;
	int changeRegionState; // -1 if not started, 0 if started and not done, 1 if done
	bool shouldFadeToBlack;
	bool shouldFadeToClear;
	double fadePercent;

	int currentRegion;

	int selectedItem;

	bool* debug;

	void tick(double dt);
	void render(double dt);
	string debugText();

	void eventHandler(sf::Event& event);

	void generateMap();
	sf::Texture* getTileset();

	GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave, bool* debug);
	~GameEnvironment();

	void tickProjectiles(double dt);
	void tickParticles(double dt);
	void summonProjectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y);
	void deleteProjectile(int index);
	void deleteParticle(int index);

	void changeRegion(int index);

	void addEntity(Entity* e);
	vector<Entity*>& getEntities();

private:
	void loadRegionEntities(int index);
	void changeRegionCallback(int index);

	sf::Vector2f cameraPos;
};

