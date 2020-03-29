#pragma once

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Camera {
public:
	Camera(sf::Vector2f center, sf::Vector2f size, float zoom);
	Camera(); // default center and size to 0

	sf::View& getView();
	void setCenter(sf::Vector2f newCenter);
	void setSize(sf::Vector2f newSize);
	void moveCenter(sf::Vector2f delta);

	sf::Vector2f getCenter();
	sf::Vector2f getSize();

private:
	sf::View view; // actual viewport object
	sf::Vector2f center;
	sf::Vector2f size;
	float zoom;
};

