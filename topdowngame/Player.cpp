#include "Player.h"

Player::Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->keys = keys;
	mainAnimation.resetToSize(1);
	mainAnimation.editFrame(0, resourceManager->getTexture("player_entity"));
	mainAnimation.editCoords(0, sf::IntRect(0, 0, 13, 18));
}

void Player::tick() {
	Entity::tick();

	//Logic for movement w/ input keys

}

void Player::render(sf::RenderWindow* window) {
	Entity::render(window);
}