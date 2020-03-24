#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	void loadTexture(std::string id, std::string imagePath);
	sf::Texture* getTexture(std::string id);

private:
	std::map<std::string, sf::Texture*> textures; // id => texture pointer
};

