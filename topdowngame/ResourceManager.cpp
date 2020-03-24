#include "ResourceManager.h"

ResourceManager::ResourceManager() {
}


ResourceManager::~ResourceManager() {
	for (auto t : textures) {
		delete t.second;
	}
}


void ResourceManager::loadTexture(std::string id, std::string imagePath) {
    sf::Texture* texture = new sf::Texture(); // create texture pointer (needs to be deleted in destructor)
   
    if (!texture->loadFromFile(imagePath)) { // load texture from image
        std::cout << "ERROR: Failed to load texture from: " << imagePath << std::endl;
        return;
    }

    if (textures.count(id)) { // make sure this texture id doesn't already exist
        std::cout << "ERROR: Texture with id \"" << id << "\" already exists. ";
        std::cout << "The new texture will not be loaded." << std::endl;
        return;
    }

    textures[id] = texture;
}

sf::Texture* ResourceManager::getTexture(std::string id) {
    if (!textures.count(id)) { // make sure that the texture actually exists
        std::cout << "ERROR: Texture with id \"" << id << "\" not found. ";
        std::cout << "Returning nullptr." << std::endl;
        return nullptr;
    }
    return textures[id];
}