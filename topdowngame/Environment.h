#include "Camera.h"

class Environment
{

public:

	Camera c;

	Environment();
	
	virtual void tick() = 0;
	virtual void render() = 0;

};

