#pragma once

#include "Camera.h"
#include "ResourceManager.h"

class Environment
{

public:

	Camera camera;
	ResourceManager resourceManager;

	Environment();
	
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void eventHandler(sf::Event& event) = 0;
};

