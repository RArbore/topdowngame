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
	h.w = 16;
	h.h = 16;
}

void Player::tick() {

	if ((*keys)["Move Up"]) {
		h.y -= 1;
	}
	if ((*keys)["Move Left"]) {
		h.x -= 1;
	}
	if ((*keys)["Move Down"]) {
		h.y += 1;
	}
	if ((*keys)["Move Right"]) {
		h.x += 1;
	}

}

void Player::render(sf::RenderWindow* window) {
	Entity::render(window);
}