#include "Environment.h"
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

	int counter;

	vector<Environment> environmentList;
	map<string, int> environmentIndices;
	Environment* currentEnvironment;

	static const int MAX_TPS = 60;

	void run();

	void initEnvironments();

	static long getMillis();

};

