#include "Camera.h"

Camera::Camera(sf::Vector2f center, sf::Vector2f size) {
	this->center = center;
	this->size = size;
	this->view.setCenter(center);
	this->view.setSize(center);
}

sf::View& Camera::getView() {
	return view;
}

void Camera::setCenter(sf::Vector2f newCenter) {
	center = newCenter;
	view.setCenter(newCenter);
}

void Camera::setSize(sf::Vector2f newSize) {
	size = newSize;
	view.setSize(newSize);
}