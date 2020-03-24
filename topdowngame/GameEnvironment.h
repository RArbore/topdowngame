#include "Environment.h"
#include "Entity.h"
#include <vector>

using namespace std;

class GameEnvironment : public Environment
{
	
public:

	vector<Entity*> entities;

	Entity* focusEntity;

	void tick();
	void render();

	GameEnvironment();

};

