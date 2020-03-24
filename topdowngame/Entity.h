#include "Hitbox.h"

#include <SFML/Graphics.hpp>

#include "Animation.h"

class Entity
{

public: // Add pointer to map object

	Hitbox h;
	
	Entity(double x, double y);

	bool moveH();
	bool moveV();

	void tick();

	void render(sf::RenderWindow& window);

private:
	sf::Sprite sprite;
	Animation mainAnimation;
};

