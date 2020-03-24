#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:
	Camera(sf::Vector2f center, sf::Vector2f size);
	Camera(); // default center and size to 0

	sf::View& getView();
	void setCenter(sf::Vector2f newCenter);
	void setSize(sf::Vector2f newSize);


private:
	sf::View view; // actual viewport object
	sf::Vector2f center;
	sf::Vector2f size;
};

