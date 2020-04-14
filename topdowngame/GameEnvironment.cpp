#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave, bool* debug) :
	Environment(window, settings, transitionEnvironment, playerSave),
	worldGenerator(WORLD_CELLS_COUNT, WORLD_MAP_SIZE, 10) // TODO: generate custom seed
{
	this->generateMap(); // create map and load into tileMap

	camera = Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 0.5);
	resourceManager.loadTexture("player_entity", "player.png");
	resourceManager.loadTexture("slime_entity", "slime.png");
	resourceManager.loadTexture("coin_entity", "coin.png");
	resourceManager.loadTexture("mushroom_entity", "mushroom.png");
	resourceManager.loadTexture("zombie_entity", "zombie.png");
	resourceManager.loadTexture("minotaur_entity", "minotaur.png");
	resourceManager.loadTexture("particle_entity", "particles.png");
	resourceManager.loadTexture("jungle_tree_entity", "jungle_trees.png");
	resourceManager.loadTexture("items_texture", "items.png");
	resourceManager.loadTexture("wands", "wands.png");
	resourceManager.loadTexture("arrow", "arrow.png");

	currentRegion = 0; // TODO: initialize this before creating the world so it starts at the right place

	projectiles = vector<Projectile*>();
	visuals = vector<Particle*>();
	
	player = new Player(this, 16, 16, &tileMap, &keys, &resourceManager);
	focusEntity = player;

	loadRegionEntities(currentRegion);

	addEntity(new Minotaur(this, 200, 200, &tileMap, &resourceManager));

	//addEntity(new Slime(this, 100, 100, &tileMap, &resourceManager));
	//addEntity(new Mushroom(this, 200, 200, &tileMap, &resourceManager));
	//addEntity(new Zombie(this, 0, 100, &tileMap, &resourceManager));

	playerSave->inventory[8] = new Item("Tier 1 Sword", "Sword", "A sword", 0, &resourceManager);
	playerSave->inventory[20] = new Item("Tier 6 Sword", "Sword", "A sword", 5, &resourceManager);
	playerSave->inventory[0] = new Item("Tier 11 Sword", "Sword", "A sword", 10, &resourceManager);
	playerSave->inventory[6] = new Item("Tier 1 Bow", "Bow", "This is a really long description! Wow, I didn't know that some items could be so complicated as to warrant such a detailed story just to be able to understand what it does at a basic level. That's pretty amazing! Who would've thought, certainly not me.", 15, &resourceManager);
	releasedR = true;
	this->debug = debug;
	selectedItem = 0;
	sf::Vector2f cameraPos((float)focusEntity->h.getCX(), (float)focusEntity->h.getCY());
}

GameEnvironment::~GameEnvironment() {
	for (auto region : entities) {
		for (auto entity : region.second) delete entity;
	}
	for (auto proj : projectiles) delete proj;
	for (auto visual : visuals) delete visual;
	delete focusEntity;
}

void GameEnvironment::tick(double dt) {
	
	player->tick(dt);
	for (int i = getEntities().size() - 1; i >= 0; i--) {
		getEntities().at(i)->tick(dt);
		if (getEntities().at(i)->removeMe) {
			if (getEntities().at(i) == focusEntity) {
				focusEntity = player;
			}
			getEntities().erase(getEntities().begin() + i);
		}
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
		if (visuals[i]->counter >= visuals[i]->timeAlive && visuals[i]->timeAlive > 0) deleteParticle(i);
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

void GameEnvironment::render(double dt) {
	sf::View prevView = window->getDefaultView();
	float dx = (float)focusEntity->h.getCX() - cameraPos.x;
	float dy = (float)focusEntity->h.getCY() - cameraPos.y;
	cameraPos.x += dx / 5;
	cameraPos.y += dy / 5;
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

	sort(getEntities().begin(), getEntities().end(), entityHeightCompare);
	sort(projectiles.begin(), projectiles.end(), entityHeightCompare);
	sort(visuals.begin(), visuals.end(), entityHeightCompare);

	vector<Entity*> intermediate(getEntities().size() + projectiles.size());
	vector<Entity*> allEntities(getEntities().size() + projectiles.size() + visuals.size());

	merge(getEntities().begin(), getEntities().end(), projectiles.begin(), projectiles.end(), intermediate.begin(), entityHeightCompare);
	merge(intermediate.begin(), intermediate.end(), visuals.begin(), visuals.end(), allEntities.begin(), entityHeightCompare);

	//player->render(window);

	bool belowPlayer = false;

	for (int i = allEntities.size() - 1; i >= 0; i--) {
		Entity* e = allEntities.at(i);
		if (e->h.getCY() + e->renderOrderOffset > player->h.getCY() + player->renderOrderOffset && !belowPlayer) {
			belowPlayer = true;
			player->render(window);
		}
		if (e->h.x >= cameraPos.x - camera.getSize().x / 2 - 200 && e->h.y >= cameraPos.y - camera.getSize().y / 2 - 200 && e->h.x + e->h.w <= cameraPos.x + camera.getSize().x / 2 + 200 && e->h.y + e->h.h <= cameraPos.y + camera.getSize().y / 2 + 200) {
			e->render(window);
		}
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

		sf::RectangleShape healthBar(sf::Vector2f((float)max(380.f*focusEntity->health/focusEntity->maxHealth, 0.), 60.f));
		healthBar.setPosition(sf::Vector2f(-float(size.x) / 2 + 20, -float(size.y) / 2 + 20));
		healthBar.setFillColor(sf::Color(220, 0, 0));

		window->draw(healthBorder);
		window->draw(healthBar);
	}

	float hotbarScale = float(size.x)/795*0.4;

	sf::RectangleShape hotbarOutline(sf::Vector2f(795*hotbarScale, 115*hotbarScale));
	hotbarOutline.setPosition(-795.f/2.f*hotbarScale, float(size.y) / 2.f - 115.f*hotbarScale);
	hotbarOutline.setFillColor(sf::Color(65, 65, 65));

	sf::RectangleShape hotbarBox(sf::Vector2f(775*hotbarScale, 95*hotbarScale));
	hotbarBox.setPosition(-795.f / 2.f * hotbarScale + 10 * hotbarScale, float(size.y) / 2.f - 115.f * hotbarScale + 10 * hotbarScale);
	hotbarBox.setFillColor(sf::Color(80, 80, 80));

	window->draw(hotbarOutline);
	window->draw(hotbarBox);

	sf::RectangleShape slot(sf::Vector2f(75.f * hotbarScale, 75.f * hotbarScale));
	slot.setFillColor(sf::Color(65, 65, 65));
	for (int i = 0; i < 9; i++) {
		if (i == selectedItem) {
			sf::RectangleShape selectedSlotBorder(sf::Vector2f(85.f * hotbarScale, 85.f * hotbarScale));
			selectedSlotBorder.setFillColor(sf::Color(95, 95, 95));
			selectedSlotBorder.setPosition(-795.f / 2.f * hotbarScale + 15 * hotbarScale + i*85*hotbarScale, float(size.y) / 2.f - 115.f * hotbarScale + 15 * hotbarScale);
			window->draw(selectedSlotBorder);
		}
		slot.setPosition(-795.f / 2.f * hotbarScale + 20 * hotbarScale + i*85*hotbarScale, float(size.y) / 2.f - 115.f * hotbarScale + 20 * hotbarScale);
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(i+8);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-795.f / 2.f * hotbarScale + 20 * hotbarScale + i*85*hotbarScale + 5.5*hotbarScale, float(size.y) / 2.f - 115.f * hotbarScale + 20 * hotbarScale + 5.5*hotbarScale);
			icon.scale(sf::Vector2f(4.f*hotbarScale, 4.f*hotbarScale));
			window->draw(icon);
			sf::RectangleShape borderCover(sf::Vector2f(75*hotbarScale, 6*hotbarScale));
			borderCover.setPosition(-795.f / 2.f * hotbarScale + 20 * hotbarScale + i*85*hotbarScale, float(size.y) / 2.f - 115.f * hotbarScale + 20 * hotbarScale + 69*hotbarScale);
			borderCover.setFillColor(sf::Color(65, 65, 65));
			window->draw(borderCover);
		}
	}
}

string GameEnvironment::debugText() {
	string ret = to_string(focusEntity->h.getCX()) + " " + to_string(focusEntity->h.getCY()) + "\n";
	Tile* tile = tileMap.getTile((int)(focusEntity->h.getCX()/16), (int)(focusEntity->h.getCY()/16));
	if (tile == NULL) {
		ret += "-1\n";
	}
	else {
		ret += to_string(tile->type) + "\n";
	}
	return ret;
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
		else {
			for (int i = 1; i < 10; i++) {
				if (event.key.code == settings->keyBindings.at("Slot "+to_string(i))) {
					selectedItem = i - 1;
					break;
				}
			}
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

	if (event.type == sf::Event::MouseWheelScrolled) {
		selectedItem = (selectedItem - (int)event.mouseWheelScroll.delta) % 9;
		while (selectedItem < 0) {
			selectedItem += 9;
		}
	}
}

void GameEnvironment::generateMap() {
	system("mkdir \"../world\"");
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
	// check if adj exists
	string filename = "../world/adj";
	struct stat buffer;
	allExist &= (stat(filename.c_str(), &buffer) == 0);

	if (!allExist) {
		worldGenerator.runAll();
		tileMap.resetTileMap(currentRegion, getTileset());
	}
	else {
		// mapDefinition = worldGenerator.sampleRegion();
		tileMap.resetTileMap(currentRegion, getTileset());
	}
}

sf::Texture* GameEnvironment::getTileset() {
	resourceManager.loadTexture("jungle_biome", "jungle_biome.png");
	return resourceManager.getTexture("jungle_biome"); // TODO: get tilemap texture
}

void GameEnvironment::summonProjectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y) {
	Projectile* proj = new Projectile(projType, x, y, vel_x, vel_y, acc_x, acc_y, &tileMap, &resourceManager);
	projectiles.push_back(proj);
}

void GameEnvironment::loadRegionEntities(int index) {
	if (entities[currentRegion].size() <= 0) {
		if (true) { //Check for region type
			map<pair<int, int>, bool> treeAtPos;
			vector<Tile*> tileVector;
			for (std::pair<std::pair<int, int>, Tile*> t : tileMap.tiles) {
				Tile* tile = t.second;
				tileVector.push_back(tile);
			}
			random_shuffle(tileVector.begin(), tileVector.end());
			for (Tile* tile : tileVector) {
				if (tile->type == 7 && rand() % 3 == 0) {
					int tx = tile->x / Tile::TILE_SIZE;
					int ty = tile->y / Tile::TILE_SIZE;
					bool check = true;
					for (int x = -2; x <= 2 && check; x++) {
						for (int y = -1; y <= 1 && check; y++) {
							Tile* neighbor = tileMap.getTile(x + tx, y + ty);
							check = neighbor != NULL && neighbor->type == 7 && !treeAtPos.count(pair<int, int>(x + tx, y + ty));
						}
					}
					if (check) {
						addEntity(new Particle(this, tile->x + 8, tile->y + 8, "jungle_tree_entity", -1, 1000000, &tileMap, &resourceManager));
						treeAtPos.insert(pair<pair<int, int>, bool>(pair<int, int>(tx, ty), true));
					}
				}
				if (tile->type == 6 && rand() % 200 == 0) {
					addEntity(new Mushroom(this, tile->x, tile->y, &tileMap, &resourceManager));
				}
				else if (tile->type == 0) {
					int r = rand() % 200;
					if (r == 0) {
						addEntity(new Slime(this, tile->x, tile->y, &tileMap, &resourceManager));
					}
					else if (r == 1) {
						addEntity(new Zombie(this, tile->x, tile->y, &tileMap, &resourceManager));
					}
				}
			}
		}
	}
}

void GameEnvironment::changeRegion(int index) {
	// TODO: there will eventually be more things here but for now it's just loading thew new file
	srand(time(NULL));
	currentRegion = index;
	tileMap.resetTileMap(index, getTileset());
	loadRegionEntities(index);
	// TODO: right now the player spawns in the middle but make it so that isn't the case
	player->h.x = (int)sqrt(tileMap.tiles.size()) / 2 * 16;
	player->h.y = (int)sqrt(tileMap.tiles.size()) / 2 * 16;
}

void GameEnvironment::addEntity(Entity* e) {
	entities[currentRegion].push_back(e);
}

vector<Entity*>& GameEnvironment::getEntities() {
	return entities[currentRegion];
}