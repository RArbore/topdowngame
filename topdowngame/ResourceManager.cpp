#include "ResourceManager.h"

std::map<std::string, sf::Texture*> ResourceManager::textures;
std::map<std::string, sf::Font*> ResourceManager::fonts;

ResourceManager::ResourceManager() {
	// sf::Texture* defaultTexture = new sf::Texture();
	// defaultTexture->create(16, 16);
	// textures["DEFAULT_TEXTURE"] = defaultTexture;
}


ResourceManager::~ResourceManager() {
	for (auto t : ResourceManager::textures) delete t.second;
	for (auto f : ResourceManager::fonts) delete f.second;
}


void ResourceManager::loadTexture(std::string id, std::string imagePath) {

	if (ResourceManager::textures.count(id)) { // make sure this texture id doesn't already exist
		std::cout << "ERROR: Texture with id \"" << id << "\" already exists. ";
		std::cout << "The new texture will not be loaded." << std::endl;
		return;
	}

	sf::Texture* texture = new sf::Texture(); // create texture pointer (needs to be deleted in destructor)
   
	if (!texture->loadFromFile("..\\spritesheets\\"+imagePath)) { // load texture from image
		std::cout << "ERROR: Failed to load texture from: " << imagePath << std::endl;
		return;
	}

	ResourceManager::textures[id] = texture;
}

sf::Texture* ResourceManager::getTexture(std::string id) {
	if (!ResourceManager::textures.count(id)) { // make sure that the texture actually exists
		std::cout << "ERROR: Texture with id \"" << id << "\" not found. ";
		std::cout << "Returning default texture." << std::endl;
		return ResourceManager::textures["DEFAULT_TEXTURE"];
	}
	return ResourceManager::textures[id];
}

void ResourceManager::loadFont(std::string id, std::string fontPath) {
	if (ResourceManager::fonts.count(id)) {
		std::cout << "ERROR: Font with id \"" << id << "\" already exists. ";
		std::cout << "The new font will not be loaded." << std::endl;
		return;
	}

	sf::Font* font = new sf::Font();
	
	if (!font->loadFromFile("../spritesheets/" + fontPath)) {
		std::cout << "ERROR: Failed to load font from: " << fontPath << std::endl;
		return;
	}

	ResourceManager::fonts[id] = font;
}