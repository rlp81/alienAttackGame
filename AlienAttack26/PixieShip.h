#pragma once
#include "gameHeader.h"
/*
* pixie.h
* Description: Header file for the ShipPixie Class and it's related constants
* Author: Cole
*/

// Pixie Ship Class, The main class for intelligent Pixies i.e. player controlled or enemies
class ShipPixie : public Pixie {
private:
	// Friend children; Pixies are designed to act as though they are all part of the same class
	friend class PlayerPixie;
	friend class EnemyPixie;
	friend class LevelLoader;

	// Friend Missile Pixie; Integrates directly with Ship Pixie and it's children
	friend class MissilePixie;
	
	// Variables
	double health; // Health of the Pixie Ship
	double damage; // Damage the Pixie Ship can do with it's attacks
	int activeMissileCount; // Amount of ship's missiles are active
	int lastMissileFrame; // Last frame the Ship fired a missile
	int ammo; // Amount of ammo the Pixie has
	float direction; // Direction the Ship is pointing
	vector<weak_ptr<MissilePixie>> missiles; // Vector of the ShipPixie's active missile IDs 
	static vector<weak_ptr<MissilePixie>> globalMissiles;
public:
	// Constructors
	ShipPixie() = delete; // Delete the default constructor, all Pixie Ships are created with a type and/or texture
	ShipPixie(int type, const std::string& textureFile); // Create a ShipPixie with both a type and a texture

	static shared_ptr<ShipPixie> create(int type, const std::string& textureFile); // Create a ShipPixie with both a type and a texture

	// Use the default Destructor and allow Shared pointer logic to handle the destruction of Pixies
	virtual ~ShipPixie() = default;

	virtual void shootMissile(); // Fire a missile from the ShipPixie
	virtual bool damagePixie(double amount); // Damage the Pixie
	static void updateAllMissiles(); // Update all of the Missiles
	void removeMissiles(); // Removes all active missiles
};
