#pragma once

#include "Effect.h"
#include "GameEnvironment.h"

class GameEnvironment;

class RegionChangeEffect : public Effect {
public:
	RegionChangeEffect(GameEnvironment* gameEnvironment);

	void trigger();
	void tick(double dt);
	void render(sf::RenderWindow* window);
	bool shouldTickOthers();

	void setRegionToChangeTo(int index);

private:
	GameEnvironment* gameEnvironment;
	double fadePercent;
	double textFadePercent;
	double textDurationCounter;
	int region;
};

