#pragma once
#include "gameHeader.h" 
/*
* PixieMissile.h
* Description: Header file for the MissilePixie Class
* Author: Cole Lehl
*/

class MissilePixie : public Pixie {
private:
	friend class Pixie;

	ShipPixie* owner; // The originator of the Missile
	float direction; // The direction the missile is traveling
	float damage; // The damage the missile willd deal
	int ownerType; // The type of the owner, used to determine what the missile can damage
public:
	// Constructors
	MissilePixie(ShipPixie* owner); // Create a MissilePixie
	MissilePixie(ShipPixie* owner, float angle); // Create a MissilePixie to travel in a specific direction
	virtual ~MissilePixie() = default; // Set the destructor to the defualt destructor

	static shared_ptr<MissilePixie> create(ShipPixie* owner); // Create a Shared Pointer MissilePixie and add it to the active missile and pixie vectors
	static shared_ptr<MissilePixie> create(ShipPixie* owner, float angle); // Create a shared pointer MissilePixie to travel in a specific direction add it to the active missile and pixie vectors

	// Logic Functions
	void update(); // Update the Missile
	bool checkCollision(); // Check if the Missile is colliding with any Pixie
	void remove(); // Remove the Pixie
	void checkForCollisions(); // Updated version of checkCollision, includes functionality instead of just pure logic checking

	// Getters and Setters
	static shared_ptr<MissilePixie> getMissileByID(int id); // Get the MissilePixie by it's ID
};