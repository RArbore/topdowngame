#include "Game.h"

Game::Game() {
	counter = 0;
	environments = map<string, Environment*>();
	main_window.create(sf::VideoMode(800, 600), "My window");
	main_window.setVerticalSyncEnabled(true);
	if (!debugScreenFont.loadFromFile("..\\spritesheets\\coders_crux.ttf"))
	{
		cout << "Could not load font to display debug screen." << endl;
	}
	debugKeyDown = false;
	showDebug = false;
	srand(time(NULL));
}

Game::~Game() {
	for (auto ge : environments) {
		delete ge.second;
	}
}

void Game::initEnvironments() {
	transitionEnvironment = "";
	environments.insert(pair<string, Environment*>("Game Environment", new GameEnvironment(&main_window, &settings, &transitionEnvironment, &playerSave, &showDebug)));
	environments.insert(pair<string, Environment*>("Inventory Environment", new InventoryEnvironment(&main_window, &settings, &transitionEnvironment, environments.at("Game Environment"), &playerSave)));
	currentEnvironment = environments.at("Game Environment");
}

void Game::run() {
	// disable OpenGL context (reactivate in render thread)
	// main_window.setActive(false);

	//std::thread renderThread(&Game::render, this);
	// renderThread.detach();

	long ptime, atime, diff = 0;
	sf::Clock clock;
	while (main_window.isOpen()) {
		ptime = getMillis();

		// handle events (the loop will end once there are no more pending events)
		sf::Event event;
		while (main_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				main_window.close();
			}
			else if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
				main_window.setView(sf::View(visibleArea));
			}

			this->handleEvents(event);
		}

		

		double dt = clock.restart().asSeconds()*(double)MAX_TPS;
		this->dt = dt;
		currentEnvironment->tick(dt);
		render(dt);

		if (!transitionEnvironment.empty()) {
			currentEnvironment = environments.at(transitionEnvironment);
			transitionEnvironment = "";
		}
		/*
		atime = getMillis();
		diff = atime - ptime;
		if (diff <= 0) {
			diff = 1;
			this_thread::sleep_for(milliseconds(1));
		}
		while (1000 / diff > MAX_TPS) {
			atime = getMillis();
			diff = atime - ptime;
			if (diff <= 0) {
				diff = 1;
			}
		}
		tps = int(1000.f / float(diff));
		*/

		atime = getMillis();
		diff = atime - ptime;
		tps = (int)(1000.f / ((float)diff));
	}
}

long Game::getMillis() {
	time_point<system_clock> now = system_clock::now();
	auto duration = now.time_since_epoch();
	return (long) duration_cast<milliseconds>(duration).count();
}

void Game::handleEvents(sf::Event& event) {
	currentEnvironment->eventHandler(event);
	if (event.type == sf::Event::KeyPressed) {
		if (!debugKeyDown && event.key.code == settings.keyBindings.at("Debug")) {
			showDebug = !showDebug;
		}
	}

	if (event.type == sf::Event::KeyReleased) {
		if (showDebug && event.key.code == settings.keyBindings.at("Debug")) {
			debugKeyDown = false;
		}
	}
}

void Game::render(double dt) {
	main_window.clear();
	currentEnvironment->render(dt);
	if (showDebug) {
		string envDebugText = currentEnvironment->debugText();
		sf::Text text;
		text.setFont(debugScreenFont);
		text.setString(to_string(tps) + "\n" + to_string(dt) + "\n" + envDebugText);
		text.setCharacterSize(24);
		sf::Vector2u size = main_window.getSize();
		sf::View defView = main_window.getDefaultView();
		defView.setCenter(sf::Vector2f(0, 0));
		defView.setSize(static_cast<sf::Vector2f>(main_window.getSize()));
		main_window.setView(defView);
		text.setPosition(sf::Vector2f(-float(size.x) / 2, -float(size.y) / 2));
		main_window.draw(text);
	}
	main_window.display();
}