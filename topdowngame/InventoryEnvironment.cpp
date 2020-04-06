#include "InventoryEnvironment.h"

InventoryEnvironment::InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background, PlayerSave* playerSave) :
	Environment(window, settings, transitionEnvironment, playerSave)
{
	this->background = background;
	counter = 0;
	releasedR = false;
}

InventoryEnvironment::~InventoryEnvironment() {

}

void InventoryEnvironment::tick() {
	counter++;
}

void InventoryEnvironment::render() {
	background->render();
	sf::View view = window->getDefaultView();
	view.setSize(static_cast<sf::Vector2f>(window->getSize()));
	view.setCenter(sf::Vector2f(0, 0));
	window->setView(view);

	sf::Vector2u size = window->getSize();

	sf::RectangleShape shade(sf::Vector2f(float(size.x), float(size.y)));
	shade.setPosition(sf::Vector2f(-float(size.x)/2, -float(size.y)/2));
	shade.setFillColor(sf::Color(0, 0, 0, 100));

	sf::RectangleShape inventoryOutline(sf::Vector2f(795, 580));
	inventoryOutline.setPosition(-400+2.5, -300+20-10);
	inventoryOutline.setFillColor(sf::Color(65, 65, 65));

	sf::RectangleShape inventoryBox(sf::Vector2f(775, 560));
	inventoryBox.setPosition(-390+2.5, -290+20-10);
	inventoryBox.setFillColor(sf::Color(80, 80, 80));

	window->draw(shade);
	window->draw(inventoryOutline);
	window->draw(inventoryBox);

	for (int armorSlot = 0; armorSlot < 3; armorSlot++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-380+2.5, -280+85*armorSlot+20-10);
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(5 + armorSlot);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-380 + 2.5 + 5.5, -280 + 85 * armorSlot + 20 - 10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
		}
	}

	for (int accessorySlot = 0; accessorySlot < 5; accessorySlot++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-280+85*accessorySlot+2.5, -280+20-10);
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(accessorySlot);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-280+85*accessorySlot+2.5 + 5.5, -280+20-10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
		}
	}

	int i = 0;

	for (int invX = 0; invX < 9; invX++) {
		for (int invY = 0; invY < 2; invY++) {
			sf::RectangleShape slot(sf::Vector2f(75, 75));
			slot.setPosition(-380+85*invX+2.5, -280+85*3+20+85*invY+20-10);
			slot.setFillColor(sf::Color(65, 65, 65));
			window->draw(slot);
			Item* itemPointer = playerSave->inventory.at(i+17);
			if (itemPointer != NULL) {
				sf::Sprite icon = itemPointer->getUnpositionedSprite();
				icon.setPosition(-380+85*invX+2.5 + 5.5, -280+85*3+20+85*invY+20-10 + 5.5);
				icon.scale(sf::Vector2f(4.f, 4.f));
				window->draw(icon);
			}
			i++;
		}
	}
	for (int invX = 0; invX < 9; invX++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-380+85*invX+2.5, -280+85*3+20+85*2+40-10);
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(invX+8);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-380+85*invX+2.5 + 5.5, -280+85*3+20+85*2+40-10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
		}
	}
}

void InventoryEnvironment::eventHandler(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == settings->keyBindings.at("Inventory") && releasedR) {
			*transitionEnvironment = "Game Environment";
			releasedR = false;
		}
	}
	else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == settings->keyBindings.at("Inventory")) {
			releasedR = true;
		}
	}
}