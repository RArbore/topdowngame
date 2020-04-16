#pragma once

#include "Effect.h"
#include "GameEnvironment.h"

class GameEnvironment;

class RegionChangeEffect : public Effect {
public:
	RegionChangeEffect(GameEnvironment* gameEnvironment);

	void trigger(int index);
	void tick(double dt);
	void render(sf::RenderWindow* window);
	bool shouldTickOthers();

private:
	GameEnvironment* gameEnvironment;
	double fadePercent;
	double textFadePercent;
	double textDurationCounter;
	int region;
};

