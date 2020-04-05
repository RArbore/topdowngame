#pragma once

#include "Environment.h"
#include "GameEnvironment.h"
#include"InventoryEnvironment.h"
#include "Settings.h"
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class Game 
{

public:

	Game();
	~Game();

	int counter;
	int tps;

	string transitionEnvironment;
	map<string, Environment*> environments;
	Environment* currentEnvironment;

	Settings settings;

	static const int MAX_TPS = 60;

	void run();

	void initEnvironments();

	static long getMillis();

private:
	sf::RenderWindow main_window;
	
	void handleEvents(sf::Event& event);
	void render();
};

