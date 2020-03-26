#pragma once

#include "Camera.h"
#include "Settings.h"
#include "ResourceManager.h"

class Environment
{

public:

	Settings* settings;
	Camera camera;
	ResourceManager resourceManager;

	Environment(sf::RenderWindow* window, Settings* settings);
	
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void eventHandler(sf::Event& event) = 0;

protected:
	sf::RenderWindow* window;
};

