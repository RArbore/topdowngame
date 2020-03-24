#include "Player.h"

Player::Player(double x, double y, TileMap* map, vector<Entity*>* entityList) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, map, entityList)
{
	//Set animation, sprite, etc
}

void Player::tick() {
	Entity::tick();

	//Logic for movement w/ input keys
}