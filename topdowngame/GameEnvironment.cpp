#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(sf::RenderWindow* window, Settings* settings):
Environment(window, settings),
tileMap(generateMap(), getTileset())
{
	entities = vector<Entity*>();
	entities.push_back(new Player(0, 0, &tileMap, &entities, &keys));
	focusEntity = entities.at(0);
	resourceManager.loadTexture("player_entity", "player.png");
	entities[0]->mainAnimation.resetToSize(1);
	entities[0]->mainAnimation.editFrame(0, resourceManager.getTexture("player_entity"));
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

	// if the focusEntity goes farther than these values along the respective axis
	// then the camera will shift to keep it within the bounds
	double horizBound = 100.f;
	double vertBound = 100.f;

	double deltaX = 0.f, deltaY = 0.f; // delta position for camera's center

	if (abs(focusEntity->h.getCX() - camera.getCenter().x) > horizBound) {
		deltaX = focusEntity->h.getCX() - camera.getCenter().x;
	}
	if (abs(focusEntity->h.getCY() - camera.getCenter().y) > vertBound) {
		deltaY = focusEntity->h.getCY() - camera.getCenter().y;
	}

	camera.moveCenter(sf::Vector2f(deltaX, deltaY));
}

void GameEnvironment::render() {
	window->setView(camera.getView());

	window->draw(tileMap);

	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->render(window);
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
	mapDefinition.resize(10, vector<int>(10, 0.f));
	return mapDefinition;
}

sf::Texture* GameEnvironment::getTileset() {
	resourceManager.loadTexture("jungle_biome", "jungle_biome.png");
	return resourceManager.getTexture("jungle_biome"); // TODO: get tilemap texture
}
