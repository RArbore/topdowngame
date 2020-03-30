#include "Game.h"

Game::Game() {
	counter = 0;
	environments = map<string, Environment*>();
	main_window.create(sf::VideoMode(800, 600), "My window");
	main_window.setVerticalSyncEnabled(true);
}

Game::~Game() {
	for (auto ge : environments) {
		delete ge.second;
	}
}

void Game::initEnvironments() {
	transitionEnvironment = "";
	environments.insert(pair<string, Environment*>("Game Environment", new GameEnvironment(&main_window, &settings, &transitionEnvironment)));
	environments.insert(pair<string, Environment*>("Inventory Environment", new GameEnvironment(&main_window, &settings, &transitionEnvironment)));
	currentEnvironment = environments.at("Game Environment");
}

void Game::run() {
	// disable OpenGL context (reactivate in render thread)
	main_window.setActive(false);

	std::thread renderThread(&Game::render, this);
	renderThread.detach();

	long ptime, atime, diff = 0;
	while (main_window.isOpen()) {

		// handle events (the loop will end once there are no more pending events)
		sf::Event event;
		while (main_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				main_window.close();
			}
			else if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				main_window.setView(sf::View(visibleArea));
			}

			this->handleEvents(event);
		}

		ptime = getMillis();

		currentEnvironment->tick();

		if (!transitionEnvironment.empty()) {
			currentEnvironment = environments.at(transitionEnvironment);
			transitionEnvironment = "";
		}

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
	}
}

long Game::getMillis() {
	time_point<system_clock> now = system_clock::now();
	auto duration = now.time_since_epoch();
	return (long) duration_cast<milliseconds>(duration).count();
}

void Game::handleEvents(sf::Event& event) {
	currentEnvironment->eventHandler(event);
}

void Game::render() {
	main_window.setActive(true);

	while (main_window.isOpen()) {
		main_window.clear();
		currentEnvironment->render();
		main_window.display();
		this_thread::sleep_for(milliseconds(1));
	}
}