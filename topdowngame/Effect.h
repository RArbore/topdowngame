#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

class Effect {
public:
	Effect() = default;

	void trigger() {};
	virtual void tick(double dt) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

protected:
	map<string, int> states;
};

