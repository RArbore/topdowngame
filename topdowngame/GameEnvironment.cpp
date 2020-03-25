#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(Settings* settings):
Environment(settings),
tileMap(generateMap(), getTileset())
{
	entities = vector<Entity*>();
	entities.push_back(new Player(0, 0, &tileMap, &entities, &keys));
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
	//TODO: Set camera pos to focusEntity

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
	std::vector<std::vector<int>> placeHolder(10, std::vector<int>(10, 0));
	return placeHolder;
	// TODO: implement a tilemap generator
}

sf::Texture* GameEnvironment::getTileset() {
	return resourceManager.getTexture(""); // TODO: get tilemap texture
}
