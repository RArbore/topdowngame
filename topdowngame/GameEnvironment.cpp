#include "GameEnvironment.h"

GameEnvironment::GameEnvironment():
tileMap(generateMap(), getTileset())
{
	entities = vector<Entity*>();
	entities.push_back(new Player(0, 0, &tileMap, &entities));
	focusEntity = entities.at(0);
}

GameEnvironment::~GameEnvironment() {
	for (auto entity : entities) {
		delete entity;
	}
}

void GameEnvironment::tick() {
	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->tick();
	}
}

void GameEnvironment::render() {

}

void GameEnvironment::eventHandler(sf::Event& event) {
	// TODO: finish this

	if (event.type == sf::Event::KeyPressed) {

	}

	if (event.type == sf::Event::KeyReleased) {

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
