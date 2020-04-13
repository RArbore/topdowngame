#pragma once

#include "Particle.h"

class Particle;
class GameEnvironment;

class JungleTree : public Particle
{

public:

	JungleTree(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager);
	JungleTree(GameEnvironment* gameEnvironment, double x, double y, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager);

private:

	void loadAnimations();

};

