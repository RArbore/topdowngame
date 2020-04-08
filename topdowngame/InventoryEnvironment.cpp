#include "InventoryEnvironment.h"

InventoryEnvironment::InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background, PlayerSave* playerSave) :
	Environment(window, settings, transitionEnvironment, playerSave)
{
	this->background = background;
	counter = 0;
	releasedR = false;
	selectedSlot = -1;
	if (!font.loadFromFile("..\\spritesheets\\coders_crux.ttf"))
	{
		cout << "Could not load font to display debug screen." << endl;
	}
}

InventoryEnvironment::~InventoryEnvironment() {

}

void InventoryEnvironment::tick(double dt) {
	counter++;

}

void InventoryEnvironment::render() {
	selectedSlot = -1;
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

	double mouseX = (double)sf::Mouse::getPosition(*window).x;
	double mouseY = (double)sf::Mouse::getPosition(*window).y;

	mouseX -= double(size.x) / 2;
	mouseY -= double(size.y) / 2;

	for (int armorSlot = 0; armorSlot < 3; armorSlot++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-380+2.5, -280+85*armorSlot+20-10);
		if (mouseX > -380 + 2.5 && mouseX <= -380 + 2.5 + 75 && mouseY > -280 + 85 * armorSlot + 20 - 10 && mouseY < -280 + 85 * armorSlot + 20 - 10 + 75) {
			selectedSlot = 5 + armorSlot;
		}
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(5 + armorSlot);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-380 + 2.5 + 5.5, -280 + 85 * armorSlot + 20 - 10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
			sf::RectangleShape borderCover(sf::Vector2f(75, 6));
			borderCover.setPosition(-380+2.5, -280+85*armorSlot+20-10 + 69);
			borderCover.setFillColor(sf::Color(65, 65, 65));
			window->draw(borderCover);
		}
	}

	for (int accessorySlot = 0; accessorySlot < 5; accessorySlot++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-280+85*accessorySlot+2.5, -280+20-10);
		if (mouseX > -280+85*accessorySlot+2.5 && mouseX <= -280+85*accessorySlot+2.5 + 75 && mouseY > -280+20-10 && mouseY < -280+20-10 + 75) {
			selectedSlot = accessorySlot;
		}
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(accessorySlot);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-280+85*accessorySlot+2.5 + 5.5, -280+20-10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
			sf::RectangleShape borderCover(sf::Vector2f(75, 6));
			borderCover.setPosition(-280+85*accessorySlot+2.5, -280+20-10 + 69);
			borderCover.setFillColor(sf::Color(65, 65, 65));
			window->draw(borderCover);
		}
	}

	int i = 0;

	for (int invX = 0; invX < 9; invX++) {
		for (int invY = 0; invY < 2; invY++) {
			sf::RectangleShape slot(sf::Vector2f(75, 75));
			slot.setPosition(-380+85*invX+2.5, -280+85*3+20+85*invY+20-10);
			if (mouseX > -380+85*invX+2.5 && mouseX <= -380+85*invX+2.5 + 75 && mouseY > -280+85*3+20+85*invY+20-10 && mouseY < -280+85*3+20+85*invY+20-10 + 75) {
				selectedSlot = i+17;
			}
			slot.setFillColor(sf::Color(65, 65, 65));
			window->draw(slot);
			Item* itemPointer = playerSave->inventory.at(i+17);
			if (itemPointer != NULL) {
				sf::Sprite icon = itemPointer->getUnpositionedSprite();
				icon.setPosition(-380+85*invX+2.5 + 5.5, -280+85*3+20+85*invY+20-10 + 5.5);
				icon.scale(sf::Vector2f(4.f, 4.f));
				window->draw(icon);
				sf::RectangleShape borderCover(sf::Vector2f(75, 6));
				borderCover.setPosition(-380+85*invX+2.5, -280+85*3+20+85*invY+20-10 + 69);
				borderCover.setFillColor(sf::Color(65, 65, 65));
				window->draw(borderCover);
			}
			i++;
		}
	}

	for (int invX = 0; invX < 9; invX++) {
		sf::RectangleShape slot(sf::Vector2f(75, 75));
		slot.setPosition(-380+85*invX+2.5, -280+85*3+20+85*2+40-10);
		if (mouseX > -380+85*invX+2.5 && mouseX <= -380+85*invX+2.5 + 75 && mouseY > -280+85*3+20+85*2+40-10 && mouseY < -280+85*3+20+85*2+40-10 + 75) {
				selectedSlot = invX+8;
			}
		slot.setFillColor(sf::Color(65, 65, 65));
		window->draw(slot);
		Item* itemPointer = playerSave->inventory.at(invX+8);
		if (itemPointer != NULL) {
			sf::Sprite icon = itemPointer->getUnpositionedSprite();
			icon.setPosition(-380+85*invX+2.5 + 5.5, -280+85*3+20+85*2+40-10 + 5.5);
			icon.scale(sf::Vector2f(4.f, 4.f));
			window->draw(icon);
			sf::RectangleShape borderCover(sf::Vector2f(75, 6));
			borderCover.setPosition(-380+85*invX+2.5, -280+85*3+20+85*2+40-10 + 69);
			borderCover.setFillColor(sf::Color(65, 65, 65));
			window->draw(borderCover);
		}
	}

	if (selectedSlot != -1 && playerSave->inventory.at(selectedSlot) != NULL) {
		playerSave->inventory.at(selectedSlot)->drawInfoBox(sf::Vector2f(mouseX, mouseY), window);
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