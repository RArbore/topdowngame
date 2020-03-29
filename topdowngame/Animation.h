#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(int size);
	Animation(); // defaults to size 0

	~Animation();

	void resetToSize(int size); // for when you want to initialize later/reset to a different size
	void editFrame(int index, sf::Texture* texture);
	void editDelay(int index, int ticks);
	void editCoords(int index, sf::IntRect coords);
	sf::Texture* getCurrentFrame(); // get current frame
	sf::IntRect getCurrentCoords(); // get current texture coords
	void play(); // update ticks and index
	void setFrame(int index); // set index to this index

private:
	int size; // number of frames
	int index; // current frame index
	int ticksCounter; // number of ticks since last frame change
	std::vector<sf::Texture*> frames;
	// delay from i to i+1 frame (wraps around to beginning) 
	// measured in number of ticks
	std::vector<int> delays;
	// coords for each frame
	std::vector<sf::IntRect> textureCoords;

	sf::Texture defaultTexture;
};

