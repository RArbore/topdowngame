#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave) :
	Environment(window, settings, transitionEnvironment, playerSave),
	tileMap(generateMap(), getTileset()),
	worldGenerator(WORLD_CELLS_COUNT, WORLD_MAP_SIZE, 10) // TODO: generate custom seed
{
	camera = Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 0.5);
	resourceManager.loadTexture("player_entity", "player.png");
	resourceManager.loadTexture("slime_entity", "slime.png");
	resourceManager.loadTexture("coin_entity", "coin.png");
	resourceManager.loadTexture("mushroom_entity", "mushroom.png");
	resourceManager.loadTexture("particle_entity", "particles.png");
	resourceManager.loadTexture("items_texture", "items.png");
	resourceManager.loadTexture("wands", "wands.png");
	resourceManager.loadTexture("arrow", "arrow.png");
	entities = vector<Entity*>();
	projectiles = vector<Projectile*>();
	visuals = vector<Particle*>();
	entities.push_back(new Player(this, 0, 0, &tileMap, &entities, &keys, &resourceManager));
	focusEntity = entities.at(0);
	player = (Player*) entities.at(0);
	entities.push_back(new Slime(this, 100, 100, &tileMap, &entities, &resourceManager));
	entities.push_back(new Mushroom(this, 200, 200, &tileMap, &entities, &resourceManager));
	playerSave->inventory[8] = new Item("Tier 1 Sword", "Sword", "A sword", 0, &resourceManager);
	playerSave->inventory[20] = new Item("Tier 6 Sword", "Sword", "A sword", 5, &resourceManager);
	playerSave->inventory[0] = new Item("Tier 11 Sword", "Sword", "A sword", 10, &resourceManager);
	playerSave->inventory[6] = new Item("Tier 1 Bow", "Bow", "A bow", 15, &resourceManager);
	releasedR = true;

	currentRegion = 0;
}

GameEnvironment::~GameEnvironment() {
	for (auto entity : entities) {
		delete entity;
	}
	for (auto proj : projectiles) delete proj;
	for (auto visual : visuals) delete visual;
	delete focusEntity;
}

void GameEnvironment::tick(double dt) {
	
	for (int i = entities.size() - 1; i >= 0; i--) {
		entities.at(i)->tick(dt);
	}

	tickProjectiles(dt);
	tickParticles(dt);
	
}

void GameEnvironment::tickProjectiles(double dt) {
	for (int i = projectiles.size() - 1; i >= 0; i--) {
		// if (projectiles[i] == nullptr) continue;
		projectiles[i]->tick(dt);

		string projType = projectiles[i]->projType;
		double cnt = projectiles[i]->durationCounter;
		if (projType == "arrow" && cnt > 50) deleteProjectile(i);
	}
}

void GameEnvironment::tickParticles(double dt) {
	for (int i = visuals.size() - 1; i >= 0; i--) {
		visuals[i]->tick(dt);
		if (visuals[i]->counter >= visuals[i]->timeAlive) deleteParticle(i);
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

void GameEnvironment::deleteParticle(int index) {
	if (index >= visuals.size()) {
		cout << "ERROR: Attempted to delete visual that doesn't exist!" << endl;
		return;
	}
	delete visuals.at(index);
	visuals.erase(visuals.begin() + index);
}

void GameEnvironment::render() {
	sf::View prevView = window->getDefaultView();
	sf::Vector2f cameraPos(focusEntity->h.getCX(), focusEntity->h.getCY());
	camera.setCenter(cameraPos);
	camera.setSize(static_cast<sf::Vector2f>(window->getSize()));
	window->setView(camera.getView());

	//Draw relative to focus

	window->draw(tileMap);

	struct {
        bool operator()(Entity* a, Entity* b) const
        {   
            return a->h.getCY() + a->renderOrderOffset > b->h.getCY() + b->renderOrderOffset;
        }   
    } entityHeightCompare;

	sort(entities.begin(), entities.end(), entityHeightCompare);
	sort(projectiles.begin(), projectiles.end(), entityHeightCompare);
	sort(visuals.begin(), visuals.end(), entityHeightCompare);

	vector<Entity*> intermediate(entities.size() + projectiles.size());
	vector<Entity*> allEntities(entities.size() + projectiles.size() + visuals.size());

	merge(entities.begin(), entities.end(), projectiles.begin(), projectiles.end(), intermediate.begin(), entityHeightCompare);
	merge(intermediate.begin(), intermediate.end(), visuals.begin(), visuals.end(), allEntities.begin(), entityHeightCompare);

	for (int i = allEntities.size() - 1; i >= 0; i--) {
		allEntities.at(i)->render(window);
	}

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
	// check if all the map files exist
	bool allExist = true;
	for (int i = 0; i < WORLD_CELLS_COUNT; i++) {
		// use hex string representation for file name
		stringstream stream;
		stream << hex << i;
		string filename(stream.str());
		filename = "../world/" + filename;

		// check if file exists
		struct stat buffer;
		allExist &= (stat(filename.c_str(), &buffer) == 0);
	}

	if (!allExist) {
		worldGenerator.runAll();
		loadRegion(currentRegion);
	}
	else {
		// mapDefinition = worldGenerator.sampleRegion();
		loadRegion(currentRegion);
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

void GameEnvironment::loadRegion(int index) {
	stringstream stream;
	stream << hex << index;
	string filename(stream.str());
	filename = "../world/" + filename;

	ifstream fin(filename);

	int expectedIndex, x1, y1, x2, y2; // use expected index as a way to assert that the region is correct
	// coordinates of upper left and lower right bounds of the region (in the world)
	fin >> expectedIndex >> x1 >> y1 >> x2 >> y2;

	assert(expectedIndex == index);

	mapDefinition.resize(x2 - x1 + 1, vector<int>(y2 - y1 + 1));

	for (int i = 0; i <= x2 - x1; i++) {
		for (int j = 0; j <= y2 - y1; j++) {
			fin >> mapDefinition[i][j];
		}
	}

	// for (int j = 0; j < y2-y1; j++) 

	fin.close();
}