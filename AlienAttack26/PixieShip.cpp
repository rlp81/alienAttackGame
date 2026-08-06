#include "gameHeader.h"
/*
* ShipPixie.cpp
* Description: function C++ file for the ShipPixie Class
* Author: Cole
*/

vector<weak_ptr<MissilePixie>> ShipPixie::globalMissiles;

/*
* ShipPixie(int type, const string& textureFile)
* Params: int type - Type of Pixie to create, string& textureFile - Texture of the Pixie
* Returns: None
* Desc: Creates a ShipPixie
*/
ShipPixie::ShipPixie(int type, const string& textureFile) : Pixie(type, textureFile) {
	activeMissileCount = 0; // Set the active amount of Missiles to 0
	lastMissileFrame = currentFrame + 30; // Set the lastMissileFrame to 30 more than the current frame so it doesn't immediately fire
	ammo = 100; // Set ammo to 100
}

/*
* create(int type, const string& textureFile)
* Params: shared_ptr<ShipPixie> type - Type of Pixie to create, string& textureFile - Texture of the Pixie
* Returns: None
* Desc: Creates a shared pointer ShipPixie and add it to the Pixies vector
*/
shared_ptr<ShipPixie> ShipPixie::create(int type, const std::string& textureFile) {
	auto pixie = make_shared<ShipPixie>(type, textureFile); // Create a Pixie with a type and texture
	pixies[pixie->pixieID] = pixie; // Add it to the Pixies vector
	return pixie; // return the ShipPixie
}

/*
* updateMissiles()
* Params: None
* Returns: None
* Desc: Updates each missiles position based on it's direction
*/
void ShipPixie::updateAllMissiles() {

	for (auto it = globalMissiles.begin(); it != globalMissiles.end();) { // Iterate through the ShipPixie's Missiles 
		shared_ptr<MissilePixie> missile = it->lock(); // Get the Missile by it's ID
		if (missile) // Check if the Missile exists
		{
			bool off = missile->isOffScreen(); // Check if it is offscreen
			if (off) {
				missile->remove(); // Remove the MissilePixie
			}
			else {
				missile->update(); // Update the MissilePixie
				missile->checkForCollisions(); // Check if it is colliding with any other Pixie
			}
			++it;
		}
		else {
			it = globalMissiles.erase(it);
		}
	}
}

/*
* shootMissile()
* Params: None
* Returns: None
* Desc: Shoots a missile in the direction the ShipPixie is facing
*/
void ShipPixie::shootMissile() {
	if (!(currentFrame >= DEFAULT_FRAMES_TILL_NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) { // Check if the ShipPixie can fire a missile based on the current frame
		return;
	}
	if (activeMissileCount >= MAX_ACTIVE_MISSILES) { // Check if there are max existing missiles
		return;
	}
	if (ammo > 0) { // Check if the ShipPixie has enough Ammo
		lastMissileFrame = currentFrame; // Set the last frame to shoot a missile to this frame
		MissilePixie::create(this); // Create a new Missile and providing it the owner/ShipPixie object
		activeMissileCount++; // Increase the active missile cound
		ammo--; // Decrease the ShipPixie's ammo
	}
	else { // If the Pixie is out of Ammo
		std::cout << "Out of ammo!" << std::endl; // Declare the ShipPixie is out of ammo
	}
}

/*
* removeMissiles()
* Params: None
* Returns: None
* Desc: Remove all current missiles created by the Pixie
*/
void ShipPixie::removeMissiles() {

	for (auto it = missiles.begin(); it != missiles.end();) {
		if (auto missile = it->lock()) { // Get the Missile by it's ID
			missile->remove();
		}
	}
	missiles.clear(); // Clear the active missiles vector
}

/*
* damagePixie(double amount)
* Params: double amount - Amount of health to be redated from the ShipPixie
* Returns: bool
* Desc: Damages the ShipPixie and return if it is dead
*/
bool ShipPixie::damagePixie(double amount) {
	health -= amount; // Removes an amount from the Pixie's health
	if (health <= 0) { // Check if the health is below or equal to 0
		Pixie::removePixieByID(this->getPixieID()); // Remove the Pixie if it is dead
		return true; // return true for dead
	}
	return false; // return false for alive
}
