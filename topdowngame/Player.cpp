#include "Player.h"

Player::Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList)
{
	this->keys = keys;
	//Set animation, sprite, etc
}

void Player::tick() {
	Entity::tick();

	//Logic for movement w/ input keys
}