#include "GameEnvironment.h"

GameEnvironment::GameEnvironment():
tileMap(generateMap(), getTileset())
{
	entities = vector<Entity*>();
	entities.push_back(new Player(0, 0, &tileMap, &entities));
	focusEntity = entities.at(0);
}

void GameEnvironment::tick() {
	for (int i = 0; i++; i < entities.size()) {
		entities.at(i)->tick();
		//Add some way to decrement i if entities.at(i) removes itself from the entity list
	}
}

void GameEnvironment::render() {

}

vector<vector<int>>& GameEnvironment::generateMap() {

}

sf::Texture* GameEnvironment::getTileset() {

}