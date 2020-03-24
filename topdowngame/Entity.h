#include "Hitbox.h"

class Entity
{

public: // Add pointer to map object

	Hitbox h;
	
	Entity(double x, double y);

	bool moveH();
	bool moveV();

	void tick();

	void render();

};

