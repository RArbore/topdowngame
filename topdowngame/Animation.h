#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(int size);
	Animation(); // defaults to size 0

	void resetToSize(int size); // for when you want to initialize later/reset to a different size
	void editFrame(int index, sf::Texture* texture);
	void editDelay(int index, int ticks);
	sf::Texture* getCurrentFrame(); // get current frame
	void play(int deltaTicks); // update ticks and index

private:
	int size; // number of frames
	int index; // current frame index
	int ticksCounter; // number of ticks since last frame change
	std::vector<sf::Texture*> frames;
	// delay from i to i+1 frame (wraps around to beginning) 
	// measured in number of ticks
	std::vector<int> delays;
};

