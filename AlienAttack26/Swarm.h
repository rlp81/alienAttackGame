#pragma once
#include "gameHeader.h"
/*
* Swarm.h
* Description: Header file for the Swarm Class and related constants
* Author: Cole Lehl
*/

// Constants

const int DEFAULT_PADDING = 10; // Default Orbit padding
const int PADDING_INCREMENT = 20; // Padding added to each Enemy orbiting

// Controller class for Enemy Pixies
class Swarm {
private:
	friend class LevelLoader; // Friend the level loader so it can access private members of the Swarm class to load and clear levels
	vector<weak_ptr<EnemyPixie>> members; // Active memebers of the Swarm
	int swarmSize; // The size of the swarm
	int targetID; // The Pixie the swarm is targeting
	weak_ptr<EnemyPixie> controller; // The Pixie the swarm is controlled by
	static vector<std::shared_ptr<Swarm>> swarms; // Vector of all existing pixies
public:
	// Constructors
	Swarm() = delete; // Delete the default constructor
	Swarm(shared_ptr<EnemyPixie> controller, vector<weak_ptr<EnemyPixie>>& members); // Create a new swarm and specify the leader and memebers
	static shared_ptr<Swarm> create(shared_ptr<EnemyPixie> controller, vector<weak_ptr<EnemyPixie>>& members);
	// Logic Functions
	void removeEnemy(int enemyID); // Remove an enemy from the swarm
	void updateSwarm(); // Update the swarm
	void setupSwarm(); // Setup the swarm
	int findNewLeader(int index); // Find a new swarm leader based on the previous leader
	static void updateAllSwarms(); // Update all existing swarms
	
	// Getters and Setters
	static int getTotalEnemyCount(); // Get the total amount of swarms
};
