#include "Game.h"

Game::Game() {
	counter = 0;
	environmentList = vector<Environment>();
	environmentIndices = map<string, int>();
}

void Game::initEnvironments() {
	environmentList.push_back(Environment());
	currentEnvironment = &environmentList[0];
	environmentIndices.insert(pair<string, int>("Test Environment", 0));
}

void Game::run() {
	long ptime, atime, diff = 0;
	while (true) {
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
}

long Game::getMillis() {
	time_point<system_clock> now = system_clock::now();
	auto duration = now.time_since_epoch();
	return duration_cast<milliseconds>(duration).count();
}