#include "RegionChangeEffect.h"

#define fadeDirection "fadeDirection"
#define textFadeDirection "textFadeDirection"
#define MAX_TEXT_DURATION 500.f

RegionChangeEffect::RegionChangeEffect(GameEnvironment* gameEnvironment) {
	this->gameEnvironment = gameEnvironment;
	this->region = -1;

	states[fadeDirection] = 0; // -1 is fade to clear, 0 is nothing, 1 is fade to black
	fadePercent = 0.f;

	states[textFadeDirection] = 0; // -1 is fade to clear, 0 is don't show, 1 is fade to opaque, 2 is stay opaque
	textFadePercent = 0.f;

	textDurationCounter = 0.f;
}

void RegionChangeEffect::trigger(int index) {
	this->index = index;
	states[fadeDirection] = 1;
	states[textFadeDirection] = 0;
	fadePercent = 0.f;
	textFadePercent = 0.f;
	textDurationCounter = 0.f;
}

void RegionChangeEffect::tick(double dt) {
	double ndt = (dt >= 5.f ? 5.f : dt);
	switch (states[fadeDirection]) {
	case 1: // fade to black
		fadePercent += 1.f * ndt;
		if (fadePercent >= 100.f) {
			fadePercent = 100.f;
			states[fadeDirection] = 0;
			gameEnvironment->changeRegionCallback(this->region);
			states[fadeDirection] = -1;
		}
		break;
	case -1: // fade to clear
		fadePercent -= 0.5 * ndt;
		if (fadePercent <= 0.f) {
			fadePercent = 0.f;
			states[fadeDirection] = 0;
			states[textFadeDirection] = 1;
		}
		break;
	case 0: // do nothing
		break;
	}

	switch (states[textFadeDirection]) {
	case 1: // fade opaque
		textFadePercent += 1.f * ndt;
		if (textFadePercent >= 100.f) {
			textFadePercent = 100.f;
			states[textFadeDirection] = 2;
		}
		break;
	case -1: // fade clear
		textFadePercent -= 0.5 * ndt;
		if (textFadePercent <= 0.f) {
			textFadePercent = 0.f;
			states[textFadeDirection] = 0;
		}
		break;
	case 2: // stay opaque
		textFadePercent = 100.f;
		textDurationCounter += 1.f * ndt;
		if (textDurationCounter >= MAX_TEXT_DURATION) {
			textDurationCounter = 0.f;
			states[textFadeDirection] = -1;
		}
		break;
	}
}

void RegionChangeEffect::render(sf::RenderWindow* window) {
	if (fadePercent > 0.f) {
		sf::RectangleShape rect(sf::Vector2f(800.f, 800.f));
		rect.setFillColor(sf::Color(0, 0, 0, 255.f * (fadePercent / 100.f)));
		sf::View view = window->getView();
		window->setView(window->getDefaultView());
		window->draw(rect);
		window->setView(view);
	}

	if (textFadePercent > 0.f && textFadePercent <= 100.f && states[textFadeDirection] != 0) {
		sf::Text text;
		text.setFont(*ResourceManager::getFont("coders_crux"));
		text.setString("Region " + to_string(region));

		sf::FloatRect textRect = text.getLocalBounds();
		// text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(-(textRect.width / 2.f), -(textRect.height / 2.f) - 100.f);

		text.setCharacterSize(50);
		text.setFillColor(sf::Color(255, 255, 255, 255.f * (textFadePercent / 100.f)));

		sf::View view = window->getView();
		window->draw(text);
	}
}

bool RegionChangeEffect::shouldTickOthers() {
	return (states[fadeDirection] != 1);
}
