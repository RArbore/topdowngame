#include "Player.h"

Player::Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->keys = keys;

	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	movementSpeed = 2.f;
	lastDirection = 0;
	health = 100;
	maxHealth = 100;
}

void Player::loadAnimations() {
	// Player Animations:
	// direction order: north, northeast, east, southeast, south, southwest, west, northwest
	// 0-7 => resting 
	// 8-15 => walking  

	sf::Texture* tex = resourceManager->getTexture("player_entity");

	// set resting animations
	for (int j = 0; j < 8; j++) {
		Animation a(1);
		a.editFrame(0, tex);
		a.editCoords(0, sf::IntRect(13 * j, 0, 13, 18));
		a.editDelay(0, 1e9);
		this->pushAnimation(a);
	}

	// set walking animations
	for (int j = 0; j < 8; j++) {
		Animation a;
		a.resetToSize(6);
		for (int i = 0; i < 6; i++) {
			a.editFrame(i, tex);
			a.editCoords(i, sf::IntRect(13 * j, 18 * i, 13, 18));
			a.editDelay(i, 5);
		}
		this->pushAnimation(a);
	}
}

void Player::tick() {

	//Check which direction the player is pressing keys to update animation
	int keyX = 0;
	int keyY = 0;

	//Move according to key presses
	if ((*keys)["Move Up"]) {
		keyY -= 1;
	}
	if ((*keys)["Move Left"]) {
		keyX -= 1;
	}
	if ((*keys)["Move Down"]) {
		keyY += 1;
	}
	if ((*keys)["Move Right"]) {
		keyX += 1;
	}

	movement(keyX, keyY);

	this->playCurrentAnimation();
}

void Player::movement(int keyX, int keyY) {
	// Player Animations:
	// direction order: north, northeast, east, southeast, south, southwest, west, northwest
	// 0-7 => resting 
	// 8-15 => walking  

	// north 
	if (keyY == -1 && keyX == 0) {
		setAnimationIndex(8);
		h.y -= movementSpeed;
	}
	// northeast
	else if (keyY == -1 && keyX == 1) {
		setAnimationIndex(9);
		h.y -= sqrt(2)/2.f*movementSpeed;
		h.x += sqrt(2)/2.f*movementSpeed;
	}
	// east
	else if (keyY == 0 && keyX == 1) {
		setAnimationIndex(10);
		h.x += movementSpeed;
	}
	// southeast
	else if (keyY == 1 && keyX == 1) {
		setAnimationIndex(11);
		h.y += sqrt(2)/2.f*movementSpeed;
		h.x += sqrt(2)/2.f*movementSpeed;
	}
	// south
	else if (keyY == 1 && keyX == 0) {
		setAnimationIndex(12);
		h.y += movementSpeed;
	}
	// southwest
	else if (keyY == 1 && keyX == -1) {
		setAnimationIndex(13);
		h.y += sqrt(2)/2.f*movementSpeed;
		h.x -= sqrt(2)/2.f*movementSpeed;
	}
	// west
	else if (keyY == 0 && keyX == -1) {
		setAnimationIndex(14);
		h.x -= movementSpeed;
	}
	// northwest
	else if (keyY == -1 && keyX == -1) {
		setAnimationIndex(15);
		h.y -= sqrt(2)/2.f*movementSpeed;
		h.x -= sqrt(2)/2.f*movementSpeed;
	}
	// resting animation (based on last direction which is 0-7)
	else setAnimationIndex(lastDirection);

	// set last direction
	lastDirection = animationIndex % 8;
}

void Player::render(sf::RenderWindow* window) {
	Entity::render(window);
}