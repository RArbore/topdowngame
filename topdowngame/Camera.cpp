#include "Camera.h"

Camera::Camera(sf::Vector2f center, sf::Vector2f size, float zoom) {
	this->center = center;
	this->size = size;
	this->view.setCenter(center);
	this->view.setSize(center);
	this->zoom = zoom;
}

Camera::Camera() {
	Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 1.0);
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
	view.zoom(zoom);
}

void Camera::moveCenter(sf::Vector2f delta) {
	view.move(delta);
}

sf::Vector2f Camera::getCenter() {
	return view.getCenter();
}

sf::Vector2f Camera::getSize() {
	return view.getSize();
}