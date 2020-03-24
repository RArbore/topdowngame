#include "Hitbox.h"

Hitbox::Hitbox(double ix, double iy, double iw, double ih) {
	x = ix;
	y = iy;
	w = iw;
	h = ih;
}

double Hitbox::getCX() {
	return x + w / 2;
}

double Hitbox::getCY() {
	return y + h / 2;
}

bool Hitbox::checkCollision(double hx, double hy, double hw, double hh) {
	double x1 = x;
	double y1 = y;
	double x2 = x + w;
	double y2 = y + h;
	double x3 = hx;
	double y3 = hy;
	double x4 = hx + hw;
	double y4 = hy + hh;
	return !(x3 > x2 || x1 > x4 || y3 > y2 || y1 > y4);
}


bool Hitbox::checkCollision(Hitbox* h) {
	return checkCollision(h->x, h->y, h->w, h->h);
}