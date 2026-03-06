#pragma once
#include "gameHeader.h"

//TODO: Create enemy Swarm class functions and logic
const int DEFAULT_PADDING = 10;
const int PADDING_INCREMENT = 20;

class Swarm {
private:
	vector<int> members;
	int swarmSize;
	int targetID;
	int controllerID;
public:
	Swarm() = delete;
	Swarm(int contollerID, vector<int> &members);
	int findNewLeader(int lastLeader);
	void changeLeader();
	void updateSwarm();
	
};
