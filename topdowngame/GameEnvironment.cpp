#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(sf::RenderWindow* window, Settings* settings) :
	Environment(window, settings),
	tileMap(generateMap(), getTileset())
{
	camera = Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 0.5);
	resourceManager.loadTexture("player_entity", "player.png");
	entities = vector<Entity*>();
	entities.push_back(new Player(0, 0, &tileMap, &entities, &keys, &resourceManager));
	focusEntity = entities.at(0);
}

GameEnvironment::~GameEnvironment() {
	for (auto entity : entities) {
		delete entity;
	}
	delete focusEntity;
}

void GameEnvironment::tick() {
	
	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->tick();
	}

	
}

void GameEnvironment::render() {
	sf::View prevView = window->getDefaultView();
	sf::Vector2f cameraPos(focusEntity->h.getCX(), focusEntity->h.getCY());
	camera.setCenter(cameraPos);
	camera.setSize(static_cast<sf::Vector2f>(window->getSize()));
	window->setView(camera.getView());

	//Draw relative to focus

	window->draw(tileMap);

	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->render(window);
	}

	//Draw at absolute positions

	prevView.setCenter(sf::Vector2f(0, 0));
	prevView.setSize(static_cast<sf::Vector2f>(window->getSize()));
	window->setView(prevView);

	if (focusEntity->maxHealth > 0) {
		sf::Vector2u size = window->getSize();
		sf::RectangleShape healthBorder(sf::Vector2f(400, 80));
		healthBorder.setPosition(sf::Vector2f(-float(size.x) / 2, -float(size.y) / 2));
		healthBorder.setFillColor(sf::Color(150, 0, 0));

		sf::RectangleShape healthBar(sf::Vector2f(380.f*focusEntity->health/focusEntity->maxHealth, 60));
		healthBar.setPosition(sf::Vector2f(-float(size.x) / 2 + 10, -float(size.y) / 2 + 10));
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
	}

	if (event.type == sf::Event::MouseButtonPressed) {

	}

	if (event.type == sf::Event::MouseButtonReleased) {

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
