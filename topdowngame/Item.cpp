#include "Item.h"

Item::Item(string itemName, string itemType, string description, int iconNumber, ResourceManager* resourceManager) {
	this->itemName = itemName;
	this->itemType = itemType;
	this->description = description;
	this->iconNumber = iconNumber;
	this->resourceManager = resourceManager;
	icons = resourceManager->getTexture("items_texture");
}

void Item::addAtrribute(Attribute attribute) {
	attributes.push_back(attribute);
}

sf::Sprite Item::getUnpositionedSprite() {
	sf::Sprite sprite = sf::Sprite();
	sprite.setTexture(*icons);
	int x = iconNumber % 16;
	int y = (int)(iconNumber / 16);
	sprite.setTextureRect(sf::IntRect(x*16, y*16, 16, 16));
	return sprite;
}

void Item::drawInfoBox(sf::Vector2f mousePos, sf::Window* window) {
	
}