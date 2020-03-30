#pragma once

#include "Environment.h"
#include "Entity.h"
#include "Player.h"
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

	map<string, bool> keys = {
		{"Move Up", false},
		{"Move Left", false},
		{"Move Down", false},
		{"Move Right", false} };

	vector<Entity*> entities;

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
};

