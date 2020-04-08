#include "Player.h"

Player::Player(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->keys = keys;
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	movementSpeed = 2.f;
	lastDirection = 0;
	health = 100;
	maxHealth = 100;
	attackDelayCounter = 0;
	isSwordAttacking = false;
	currentAttackAngle = 0.f;
	endAttackAngle = 0.f;
}

void Player::loadAnimations() {
	// Player Animations:
	// direction order: north, northeast, east, southeast, south, southwest, west, northwest
	// 0-7 => resting 
	// 8-15 => walking  

	sf::Texture* tex = resourceManager->getTexture("player_entity");

	// set resting animations
	for (int j = 0; j < 8; j++) {
		Animation* a = new Animation(1);
		a->editFrame(0, tex);
		a->editCoords(0, sf::IntRect(13 * j, 0, 13, 18));
		a->editDelay(0, 1e9);
		this->pushAnimation(a);
	}

	// set walking animations
	for (int j = 0; j < 8; j++) {
		Animation* a = new Animation(6);
		for (int i = 0; i < 6; i++) {
			a->editFrame(i, tex);
			a->editCoords(i, sf::IntRect(13 * j, 18 * i, 13, 18));
			a->editDelay(i, 5);
		}
		this->pushAnimation(a);
	}
}

void Player::tick(double dt) {
	attackDelayCounter += dt;

	if (isSwordAttacking) {
		currentAttackAngle += dt;
		if (currentAttackAngle >= endAttackAngle) {
			isSwordAttacking = false;
			currentAttackAngle = 0.f;
			endAttackAngle = 0.f;
		}
	}

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
	if ((*keys)["Left Click"]) {
		if (attackDelayCounter >= 10.f && !isSwordAttacking) {
			isSwordAttacking = true;

			double dx = mouseX - screenX;
			double dy = mouseY - screenY;
			double PI = 3.14159265;
			currentAttackAngle = (atan2(dy, dx) * 180.f / PI) + 270.f;
			if (currentAttackAngle > 360) currentAttackAngle -= 360.f;
			endAttackAngle = currentAttackAngle + 60.f;

			/*
			// fire projectile
			double dx = mouseX - screenX;
			double dy = mouseY - screenY;
			double mag = sqrt(dx * dx + dy * dy);
			if (mag == 0.f) mag = 1.f;
			dx /= mag;
			dy /= mag;

			double speedMultiplier = 0.f;
			string projType = "arrow"; // TODO: use inventory or something to determine this
			if (projType == "arrow") speedMultiplier = 5.f;

			dx *= speedMultiplier;
			dy *= speedMultiplier;
			gameEnvironment->summonProjectile(projType, h.getCX(), h.getCY(), dx, dy, 0.f, 0.f);

			attackDelayCounter = 0.f;
			*/
		}
	}

	movement(keyX, keyY, dt);

	if ((keyX != 0 || keyY != 0) && rand() % 2 == 0) {
		gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX(), h.getCY()+7, 1, -1000000, tileMap, entityList, resourceManager));
	}

	this->playCurrentAnimation(dt);
}

void Player::movement(int keyX, int keyY, double dt) {
	// Player Animations:
	// direction order: north, northeast, east, southeast, south, southwest, west, northwest
	// 0-7 => resting 
	// 8-15 => walking  

	double mv = dt * movementSpeed;

	// if attacking, use attacking direction instead of movement direction
	// north 
	if (keyY == -1 && keyX == 0) {
		// setAnimationIndex(8);
		h.y -= mv;
	}
	// northeast
	else if (keyY == -1 && keyX == 1) {
		// setAnimationIndex(9);
		h.y -= sqrt(2) / 2.f * mv;
		h.x += sqrt(2) / 2.f * mv;
	}
	// east
	else if (keyY == 0 && keyX == 1) {
		// setAnimationIndex(10);
		h.x += mv;
	}
	// southeast
	else if (keyY == 1 && keyX == 1) {
		// setAnimationIndex(11);
		h.y += sqrt(2) / 2.f * mv;
		h.x += sqrt(2) / 2.f * mv;
	}
	// south
	else if (keyY == 1 && keyX == 0) {
		// setAnimationIndex(12);
		h.y += mv;
	}
	// southwest
	else if (keyY == 1 && keyX == -1) {
		// setAnimationIndex(13);
		h.y += sqrt(2) / 2.f * mv;
		h.x -= sqrt(2) / 2.f * mv;
	}
	// west
	else if (keyY == 0 && keyX == -1) {
		// setAnimationIndex(14);
		h.x -= mv;
	}
	// northwest
	else if (keyY == -1 && keyX == -1) {
		// setAnimationIndex(15);
		h.y -= sqrt(2) / 2.f * mv;
		h.x -= sqrt(2) / 2.f * mv;
	}
	// resting animation (based on last direction which is 0-7)
	// else setAnimationIndex(lastDirection);

	// if mouse is pressed, override direction to direction of mouse
	if ((*keys)["Left Click"]) {
		double dx = mouseX - screenX;
		double dy = mouseY - screenY;
		double PI = 3.14159265;
		double angle = (int) (atan2(dy, dx) * 180.f / PI);
		// if (dx < 0) angle += 180.f;

		// cout << angle << endl;

		bool moving = (keyX != 0 || keyY != 0) ? true : false;
		
		int baseIndex = 0;
		// north -112.5 -> -67.5
		if (angle > -112.5 && angle <= -67.5) baseIndex = 0;
		// northeast -67.5 -> -22.5
		else if (angle > -67.5 && angle <= -22.5) baseIndex = 1;
		// east -22.5 -> 22.5
		else if (angle > -22.5 && angle <= 22.5) baseIndex = 2;
		// southeast 22.5 -> 67.5
		else if (angle > 22.5 && angle <= 67.5) baseIndex = 3;
		// south 67.5 -> 112.5
		else if (angle > 67.5 && angle <= 112.5) baseIndex = 4;
		// southwest 112.5 -> 157.5
		else if (angle > 112.5 && angle <= 157.5) baseIndex = 5;
		// west 157.5 -> 180, -180 -> -157.5
		else if ((angle > 157.5 && angle <= 180) || (angle >= -180 && angle <= -157.5)) baseIndex = 6;
		// northwest -157.5 -> -112.5
		else if (angle > -157.5 && angle <= -112.5) baseIndex = 7;

		baseIndex += moving ? 8 : 0;
		setAnimationIndex(baseIndex);
	}
	else {
		if (keyY == -1 && keyX == 0) setAnimationIndex(8);
		// northeast
		else if (keyY == -1 && keyX == 1) setAnimationIndex(9);
		// east
		else if (keyY == 0 && keyX == 1) setAnimationIndex(10);
		// southeast
		else if (keyY == 1 && keyX == 1) setAnimationIndex(11);
		// south
		else if (keyY == 1 && keyX == 0) setAnimationIndex(12);
		// southwest
		else if (keyY == 1 && keyX == -1) setAnimationIndex(13);
		// west
		else if (keyY == 0 && keyX == -1) setAnimationIndex(14);
		// northwest
		else if (keyY == -1 && keyX == -1) setAnimationIndex(15);
		// resting animation (based on last direction which is 0-7)
		else setAnimationIndex(lastDirection);
	}

	// set last direction
	lastDirection = animationIndex % 8;
}

void Player::render(sf::RenderWindow* window) {

	// update values used for projectile firing and player direction
	mouseX = (double)sf::Mouse::getPosition(*window).x;
	mouseY = (double)sf::Mouse::getPosition(*window).y;

	screenX = (window->mapCoordsToPixel(sf::Vector2f(h.getCX(), h.getCY()))).x;
	screenY = (window->mapCoordsToPixel(sf::Vector2f(h.getCX(), h.getCY()))).y;

	if (isSwordAttacking) {
		/*
		sf::RectangleShape sword(sf::Vector2f(16, 16));
		sword.setRotation(currentAttackAngle);
		sword.setPosition(h.getCX(), h.getCY());
		sword.setFillColor(sf::Color::White);
		window->draw(sword);
		*/
		
		swordSprite.setTexture(*(resourceManager->getTexture("items_texture")));
		swordSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

		sf::Transform tr;
		tr.rotate(currentAttackAngle, h.getCX()+0.f, h.getCY()+16.f);
		tr.translate(h.getCX(), h.getCY()+16);

		// swordSprite.setRotation(currentAttackAngle);
		// swordSprite.setPosition(h.getCX(), h.getCY());

		window->draw(swordSprite, tr);
		
	}

	Entity::render(window);
}