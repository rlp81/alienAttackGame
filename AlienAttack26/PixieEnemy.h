#pragma once
#include "gameHeader.h" 
/*
* PixieEnemy.h
* Description: Header file for the PixieEnemy Class and it's related constants
* Author: Cole Lehl
*/

// Pixie controller for the game's enemies, based on the ShipPixie
class EnemyPixie : public ShipPixie {
private:
	friend class Swarm; // Friend the class swarm so it can access private members
	string faction; // Faction the enemie is a part of, unused
	int enemyType; // The type of enemy
	int movePattern; // The pattern of movement the enemy follows
	int targetType; // The type of targeting the enemy will use
	int orbitDirection; // The direction the enemy will orbit
	shared_ptr<Pixie> target; // The Pixie pointer of the target
	int leader; // The ID of the leader of the swarm, if applicable
	int followPadding; // The padding between the enemy and the leader
	bool canFireMissile; // A boolean of whether the enemy can fire a missile
public:
	// Constructor
	EnemyPixie(); // The main constructor to create an EnemyPixie

	// Static Functions
	static shared_ptr<EnemyPixie> create(); // Create a shared pointer EnemyPixie and add it to the Pixie vector
	static shared_ptr<EnemyPixie> create(int targetID); // Create a shared pointer EnemyPixie with a target and add it to the Pixie vector
	static vector<int> enemies; // Static vector of all active Enemy IDs

	// Logic Functions
	void orbit(); // Orbit the selected target or leader
	void orbit(float radius, shared_ptr<Pixie> target); // Orbit the target with a predefined radius
	void followTarget(); // Follow the selected target or leader
	void shootMissile(); // Shoot a missile
	void followTarget(shared_ptr<Pixie> target); // Follow the a specified target 
	void update(); // Update the enemy

	// Getters and Setters
	void setFollowPadding(int padding) { followPadding = padding; } // Set the follow padding
	int getFollowPadding() { return followPadding; } // Get the follow padding
	shared_ptr<Pixie> getTarget() const { return target; } // Get the selected target
	void setPattern(int pattern) { movePattern = pattern; } // Set the move pattern of the EnemyPixie
	void changeOrbitDirection() { orbitDirection *= -1; } // Change the direction the Enemy is orbiting
};
