#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class ResourceManager {
public:

	static void loadTexture(std::string id, std::string imagePath);
	static sf::Texture* getTexture(std::string id);

	static void loadFont(std::string id, std::string fontPath);
	static sf::Font* getFont(std::string id);

	static std::map<std::string, sf::Texture*> textures; // id => texture pointer
	static std::map<std::string, sf::Font*> fonts; // id => font pointer

private:
	ResourceManager();
	~ResourceManager();
};

