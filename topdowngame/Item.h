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

	ResourceManager* resourceManager;

	Item(string itemName, string itemType, string description, int iconNumber, ResourceManager* resourceManager);

	void addAtrribute(Attribute attribute);

	sf::Sprite getUnpositionedSprite();

};

