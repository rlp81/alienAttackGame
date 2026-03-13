#pragma once
#include "gameHeader.h" 
/*
* PixiePlayer.h
* Description: Header file for the PixiePlayer Class
* Author: Cole Lehl
*/

// Pixie controller for a player controlled Pixie, inherets from ShipPixie
class PlayerPixie : public ShipPixie {
private:
	friend class MissilePixie; // Friend the Missile Pixie so that the Missile Pixie can access the PlayerPixie
public:
	// Constructors
	PlayerPixie(); // Create a PlayerPixie
	static shared_ptr<PlayerPixie> create(); // Create a shared pointer PlayerPixie and add it to the active Pixies vector

	// Logic Functions
	void update(); // Update the PlayerPixie

};