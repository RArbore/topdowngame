#include "Player.h"

Player::Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->keys = keys;
	//Set animation, sprite, etc
}

void Player::tick() {
	Entity::tick();

	//Logic for movement w/ input keys

}

void Player::render(sf::RenderWindow* window) {
	Entity::render(window);
}