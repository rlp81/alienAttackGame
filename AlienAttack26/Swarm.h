#pragma once
#include "gameHeader.h"

class Swarm {
private:
	vector<int> enemies;
	int swarmSize;
	int targetID;
	int controllerID;
public:
	void updateSwarm();
};
