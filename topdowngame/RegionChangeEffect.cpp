#include "RegionChangeEffect.h"

#define fadeDirection "fadeDirection"

RegionChangeEffect::RegionChangeEffect(GameEnvironment* gameEnvironment) {
	this->gameEnvironment = gameEnvironment;

	states[fadeDirection] = 0; // -1 is fade to clear, 0 is nothing, 1 is fade to black
	fadePercent = 0.f;
}

void RegionChangeEffect::trigger() {
	states[fadeDirection] = 1;
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
			states["fadeDirection"] = 0;
		}
		break;
	case 0: // do nothing
		break;
	}
}

void RegionChangeEffect::render(sf::RenderWindow* window) {
	if (fadePercent >= 0.f) {
		sf::RectangleShape rect(sf::Vector2f(800.f, 800.f));
		rect.setFillColor(sf::Color(0, 0, 0, 255.f * (fadePercent / 100.f)));
		sf::View view = window->getView();
		window->setView(window->getDefaultView());
		window->draw(rect);
		window->setView(view);
	}
}

bool RegionChangeEffect::shouldTickOthers() {
	return (states[fadeDirection] != 1);
}

void RegionChangeEffect::setRegionToChangeTo(int index) {
	this->region = index;
}