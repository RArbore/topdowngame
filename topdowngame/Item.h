#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Attribute.h"
#include "ResourceManager.h"

using namespace std;

class Item
{

public:

	string itemName;

	string itemType;

	string description;

	vector<Attribute> attributes;

	sf::Texture* icons;

	int iconNumber;

	Item(string itemName, string itemType, string description, int iconNumber);

	void addAtrribute(Attribute attribute);

	sf::Sprite getUnpositionedSprite();

	vector<string> splitString(string input, char c);

	void placeEnters(string input, sf::Text* text, int limit);

	void drawInfoBox(double mouseX, double mouseY, sf::RenderWindow* window, sf::Font* font);

};

