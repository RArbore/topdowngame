#pragma once

#include "Camera.h"
#include "Settings.h"
#include "ResourceManager.h"
#include "PlayerSave.h"

class Environment
{

public:

	Settings* settings;
	Camera camera;
	ResourceManager resourceManager;

	string* transitionEnvironment;

	PlayerSave* playerSave;

	Environment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave);
	
	virtual void tick(double dt) = 0;
	virtual void render(double dt) = 0;
	virtual void eventHandler(sf::Event& event) = 0;

protected:
	sf::RenderWindow* window;
};

