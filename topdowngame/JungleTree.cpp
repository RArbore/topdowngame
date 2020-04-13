#include "JungleTree.h"

JungleTree::JungleTree(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager) :
Particle::Particle(gameEnvironment, x, y, 0, tileMap, resourceManager)
{
	this->loadAnimations();
	timeAlive = -1;
}

JungleTree::JungleTree(GameEnvironment* gameEnvironment, double x, double y, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager) :
Particle::Particle(gameEnvironment, x, y, 0, renderOrderOffset, tileMap, resourceManager)
{
	this->loadAnimations();
	timeAlive = -1;
}

void JungleTree::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("jungle_tree_entity");

	Animation* a = new Animation(1);
	a->editFrame(0, tex);
	a->editCoords(0, sf::IntRect(0, 0, 80, 96));
	a->editDelay(0, 1e9);
	this->pushAnimation(a);
}