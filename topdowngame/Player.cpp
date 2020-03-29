#include "Player.h"

Player::Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->keys = keys;
	Animation mainAnimation;
	mainAnimation.resetToSize(1);
	mainAnimation.editFrame(0, resourceManager->getTexture("player_entity"));
	mainAnimation.editCoords(0, sf::IntRect(0, 0, 13, 18));
	this->pushAnimation(mainAnimation);

	h.w = 16;
	h.h = 16;
}

void Player::tick() {

	//Check which direction the player is pressing keys to update animation
	int keyX = 0;
	int keyY = 0;

	//Move according to key presses
	if ((*keys)["Move Up"]) {
		h.y -= 1;
		keyY -= 1;
	}
	if ((*keys)["Move Left"]) {
		h.x -= 1;
		keyX -= 1;
	}
	if ((*keys)["Move Down"]) {
		h.y += 1;
		keyY += 1;
	}
	if ((*keys)["Move Right"]) {
		h.x += 1;
		keyX += 1;
	}

	updateAnimation(keyX, keyY);

}

void Player::updateAnimation(int keyX, int keyY) {
	//@Sanketh, keyX and keyY refer to what combo of x & y directions player is inputting, update animations accordingly
}

void Player::render(sf::RenderWindow* window) {
	Entity::render(window);
}