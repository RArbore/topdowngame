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

vector<string> Item::splitString(string input, char c) {
	string buff = "";
	vector<string> v;
	
	for(auto n:input) {
		if(n != c) buff+=n; 
		else if(n == c && buff != "") { 
			v.push_back(buff); 
			buff = ""; 
		}
	}

	if(buff != "") v.push_back(buff);
	
	return v;
}

void Item::placeEnters(string input, sf::Text* text, int limit) {
	float width;
	text->setString("");
	vector<string> words = splitString(input, ' ');
	for (int i = 0; i < words.size(); i++) {
		string prevString = text->getString();
		text->setString(prevString + words.at(i) + " ");
		width = text->getLocalBounds().width;
		if (width > 300) {
			prevString += "\n" + words.at(i);
			text->setString(prevString+" ");
		}
	}
}

void Item::drawInfoBox(double mouseX, double mouseY, sf::RenderWindow* window, sf::Font* font) {
	mouseX += 15;

	sf::Text name;
	name.setFont(*font);
	name.setString(itemName);
	name.setCharacterSize(32);
	name.setPosition(sf::Vector2f(mouseX+10, mouseY-6));
	float nameHeight = name.getLocalBounds().height;

	sf::Text description;
	description.setFont(*font);
	description.setString(this->description);
	description.setCharacterSize(24);
	description.setPosition(sf::Vector2f(mouseX+10, mouseY+nameHeight+10));

	float nameWidth = name.getLocalBounds().width;
	float descriptionWidth = description.getLocalBounds().width;
	float width = std::max(nameWidth, std::min(descriptionWidth, 400.f));

	if (descriptionWidth > 300) {
		placeEnters(description.getString(), &description, 400);
	}

	this->description = description.getString();

	float descriptionHeight = description.getLocalBounds().height;
	float height = nameHeight + descriptionHeight;

	sf::RectangleShape outline(sf::Vector2f(width+20, height+35));
	outline.setPosition(sf::Vector2f(mouseX, mouseY));
	outline.setFillColor(sf::Color(50, 50, 50));
	sf::RectangleShape box(sf::Vector2f(width+10, height+25));
	box.setPosition(sf::Vector2f(mouseX+5, mouseY+5));
	box.setFillColor(sf::Color(65, 65, 65));

	window->draw(outline);
	window->draw(box);
	window->draw(name);
	window->draw(description);
}