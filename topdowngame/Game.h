#include "Environment.h"
#include "GameEnvironment.h"
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class Game 
{

public:

	Game();
	~Game();

	int counter;

	map<string, Environment*> environments;
	Environment* currentEnvironment;

	static const int MAX_TPS = 60;

	void run();

	void initEnvironments();

	static long getMillis();

private:
	

};

