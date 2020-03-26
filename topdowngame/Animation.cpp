#include "Animation.h"

Animation::Animation(int size) {
    this->resetToSize(size);
    defaultTexture = new sf::Texture();
    defaultTexture->create(16, 16);
}

Animation::Animation() {
    this->resetToSize(0);
    defaultTexture = new sf::Texture();
    defaultTexture->create(16, 16);
}

void Animation::resetToSize(int size) {
    if (size < 0) {
        std::cout << "Cannot have animation with negative length. Defaulting to 0." << std::endl;
        size = 0;
    }
    this->size = size;
    this->index = 0;
    this->ticksCounter = 0;
    this->frames.resize(size);
    this->delays.resize(size);
}

Animation::~Animation() {
    delete defaultTexture;
}

void Animation::editFrame(int index, sf::Texture* texture) {
    if (index >= frames.size()) {
        std::cout << "ERROR: Frame index out of bounds. Did not edit frame." << std::endl;
        return;
    }
    frames[index] = texture;
}

void Animation::editDelay(int index, int ticks) {
    if (index >= frames.size() - 1) {
        std::cout << "ERROR: Delay index out of bounds. Did not edit delay." << std::endl;
        return;
    }
    delays[index] = ticks;
}

sf::Texture* Animation::getCurrentFrame() {
    if (frames.size() <= 0) {
        std::cout << "ERROR: Tried to acccess frames that don't exist!";
        std::cout << "Returning default texture." << std::endl;
        return defaultTexture;
    }
    return frames[index];
}

void Animation::play(int deltaTicks) {
    ticksCounter += deltaTicks;
    if (ticksCounter >= delays[index]) {
        index += 1;
        ticksCounter = 0;
    }
}