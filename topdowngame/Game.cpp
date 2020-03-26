#include "Game.h"

Game::Game() :
settings()
{
	counter = 0;
	environments = map<string, Environment*>();
	main_window.create(sf::VideoMode(800, 600), "My window");
}

Game::~Game() {
	for (auto ge : environments) {
		delete ge.second;
	}
}

void Game::initEnvironments() {
	Settings* settingsP = &settings;
	environments.insert(pair<string, Environment*>("Test Environment", new GameEnvironment(settingsP)));
	currentEnvironment = environments.at("Test Environment");
}

void Game::run() {
	// disable OpenGL context (reactivate in render thread)
	main_window.setActive(false);

	std::thread renderThread(&Game::render, this);
	//sf::Thread renderThread(&Game::render, this);
	//renderThread.launch();

	long ptime, atime, diff = 0;
	while (main_window.isOpen()) {

		// handle events (the loop will end once there are no more pending events)
		sf::Event event;
		while (main_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				main_window.close();
			}

			this->handleEvents(event);
		}

		ptime = getMillis();

		//Tick current environment

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
	}

	// wait until render thread finishes before making it go out of scope
	// guaranteed to finish since the loop breaks (window not open)
	renderThread.join();
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
		currentEnvironment->render();
		this_thread::sleep_for(milliseconds(100));
		main_window.clear();
		main_window.display();
	}
}