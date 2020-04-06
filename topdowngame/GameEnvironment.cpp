#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave) :
	Environment(window, settings, transitionEnvironment, playerSave),
	tileMap(generateMap(), getTileset())
{
	camera = Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 0.5);
	resourceManager.loadTexture("player_entity", "player.png");
	resourceManager.loadTexture("items_texture", "items.png");
	resourceManager.loadTexture("wands", "wands.png");
	entities = vector<Entity*>();
	entities.push_back(new Player(this, 0, 0, &tileMap, &entities, &keys, &resourceManager));
	focusEntity = entities.at(0);
	playerSave->inventory[8] = new Item("Tier 1 Sword", "Sword", "A basic sword", 0, &resourceManager);
	releasedR = true;
}

GameEnvironment::~GameEnvironment() {
	for (auto entity : entities) {
		delete entity;
	}
	for (auto proj : projectiles) delete proj;
	delete focusEntity;
}

void GameEnvironment::tick(double dt) {
	
	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->tick(dt);
	}

	tickProjectiles(dt);
	
}

void GameEnvironment::tickProjectiles(double dt) {
	for (int i = projectiles.size() - 1; i >= 0; i--) {
		// if (projectiles[i] == nullptr) continue;
		projectiles[i]->tick(dt);

		string projType = projectiles[i]->projType;
		double cnt = projectiles[i]->durationCounter;
		if (projType == "basic" && cnt > 50) deleteProjectile(i);
	}
}

void GameEnvironment::deleteProjectile(int index) {
	if (index >= projectiles.size()) {
		cout << "ERROR: Attempted to delete projectile that doesn't exist!" << endl;
		return;
	}
	delete projectiles.at(index);
	projectiles.erase(projectiles.begin() + index);
}

void GameEnvironment::render() {
	sf::View prevView = window->getDefaultView();
	sf::Vector2f cameraPos(focusEntity->h.getCX(), focusEntity->h.getCY());
	camera.setCenter(cameraPos);
	camera.setSize(static_cast<sf::Vector2f>(window->getSize()));
	window->setView(camera.getView());

	//Draw relative to focus

	window->draw(tileMap);

	for (int i = entities.size() - 1; i >= 1; i--) {
		entities.at(i)->render(window);
	}

	for (int i = projectiles.size() - 1; i >= 0; i--) {
		// if (projectiles.at(i) == nullptr) continue;
		projectiles.at(i)->render(window);
	}

	((Player*)focusEntity)->render(window);

	//Draw at absolute positions

	prevView.setCenter(sf::Vector2f(0, 0));
	prevView.setSize(static_cast<sf::Vector2f>(window->getSize()));
	window->setView(prevView);

	sf::Vector2u size = window->getSize();

	if (focusEntity->maxHealth > 0) {
		sf::RectangleShape healthBorder(sf::Vector2f(400, 80));
		healthBorder.setPosition(sf::Vector2f(-float(size.x) / 2 + 10, -float(size.y) / 2 + 10));
		healthBorder.setFillColor(sf::Color(150, 0, 0));

		sf::RectangleShape healthBar(sf::Vector2f(max(380.f*focusEntity->health/focusEntity->maxHealth, 0.), 60));
		healthBar.setPosition(sf::Vector2f(-float(size.x) / 2 + 20, -float(size.y) / 2 + 20));
		healthBar.setFillColor(sf::Color(220, 0, 0));

		window->draw(healthBorder);
		window->draw(healthBar);
	}
}

void GameEnvironment::eventHandler(sf::Event& event) {
	// TODO: finish this

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == settings->keyBindings.at("Move Up")) {
			keys["Move Up"] = true;
		}
		else if (event.key.code == settings->keyBindings.at("Move Left")) {
			keys["Move Left"] = true;
		}
		else if (event.key.code == settings->keyBindings.at("Move Down")) {
			keys["Move Down"] = true;
		}
		else if (event.key.code == settings->keyBindings.at("Move Right")) {
			keys["Move Right"] = true;
		}
		else if (event.key.code == settings->keyBindings.at("Inventory") && releasedR) {
			*transitionEnvironment = "Inventory Environment";
			releasedR = false;
			keys["Move Up"] = false;
			keys["Move Left"] = false;
			keys["Move Down"] = false;
			keys["Move Right"] = false;
		}
	}

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == settings->keyBindings.at("Move Up")) {
			keys["Move Up"] = false;
		}
		else if (event.key.code == settings->keyBindings.at("Move Left")) {
			keys["Move Left"] = false;
		}
		else if (event.key.code == settings->keyBindings.at("Move Down")) {
			keys["Move Down"] = false;
		}
		else if (event.key.code == settings->keyBindings.at("Move Right")) {
			keys["Move Right"] = false;
		}
		else if (event.key.code == settings->keyBindings.at("Inventory")) {
			releasedR = true;
		}
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			keys["Left Click"] = true;
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			keys["Left Click"] = false;
		}
	}
}

vector<vector<int>>& GameEnvironment::generateMap() {
	mapDefinition.resize(50, vector<int>(50, 0.f));
	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {
			mapDefinition[x][y] = float(rand() % 29);
		}
	}
	return mapDefinition;
}

sf::Texture* GameEnvironment::getTileset() {
	resourceManager.loadTexture("jungle_biome", "jungle_biome.png");
	return resourceManager.getTexture("jungle_biome"); // TODO: get tilemap texture
}

void GameEnvironment::summonProjectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y) {
	Projectile* proj = new Projectile(projType, x, y, vel_x, vel_y, acc_x, acc_y, &tileMap, &entities, &resourceManager);
	projectiles.push_back(proj);
}
