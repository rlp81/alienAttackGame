#include "gameHeader.h"
/*
* PixieMissile.cpp
* Description: function C++ file for the PixieMissile Class
* Author: Cole Lehl
*/

// Constructors

/*
* MissilePixie(ShipPixie* owner)
* Params: ShipPixie* owner - The originator of the Missile
* Returns: None
* Desc: Creates an MissilePixie
*/
MissilePixie::MissilePixie(ShipPixie* owner) : Pixie(PIXIE_TYPE_MISSILE, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED); // Set the Speed to the default missile speed
	this->owner = owner; // Set the owner to the originator of the missile
	this->setPosition(owner->getPosition()); // Set the position and rotation of the missile to that of the owner
	this->setRotation(owner->getRotation());
	this->damage = owner->damage; // Set the Missile's damage to the damage of the owner
}

/*
* MissilePixie(ShipPixie* owner, float angle)
* Params: ShipPixie* owner - The originator of the Missile, float angle - The angle for the Missile to travel
* Returns: None
* Desc: Creates an MissilePixie and makes it travel in a specific direction
*/
MissilePixie::MissilePixie(ShipPixie* owner, float angle) : Pixie(2, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED); // Set the Speed to the default missile speed
	this->owner = owner; // Set the owner to the originator of the missile
	this->setPosition(owner->getPosition());// Set the position of the missile to that of the owner
	direction = angle; // Set the direction for the PixieMissile to travel to the provided angle
	this->setRotation(degrees(direction)); // Angle the PixieMissile to the provided angle
	this->damage = owner->damage; // Set the Missile's damage to the damage of the owner
}


/*
* create(ShipPixie* owner)
* Params: ShipPixie* owner - The originator of the Missile
* Returns: shared_ptr<MissilePixie>
* Desc: Creates an MissilePixie and adds it to the active missile and pixie vectors
*/
shared_ptr<MissilePixie> MissilePixie::create(ShipPixie* owner) {
	auto missile = make_shared<MissilePixie>(owner); // Create a shared pointer of a MissilePixie
	pixies.push_back(missile); // Place the MissilePixie into the active Pixies vector
	owner->missiles.push_back(missile->getPixieID()); // Add the MissilePixie's ID into the originator's active missile vector
	return missile; // Return the MissilePixie
}

/*
* MissilePixie(ShipPixie* owner, float angle)
* Params: ShipPixie* owner - The originator of the Missile, float angle - The angle for the Missile to travel
* Returns: shared_ptr<MissilePixie>
* Desc: Creates an MissilePixie and adds it to the active missile and pixie vectors
*/
shared_ptr<MissilePixie> MissilePixie::create(ShipPixie* owner, float angle) {
	auto missile = make_shared<MissilePixie>(owner, angle); // Create a shared pointer of a MissilePixie
	pixies.push_back(missile); // Place the MissilePixie into the active Pixies vector
	owner->missiles.push_back(missile->getPixieID()); // Add the MissilePixie's ID into the originator's active missile vector
	return missile; // Return the MissilePixie
}

// Logic Functions

/*
* update()
* Params: None
* Returns: None
* Desc: Updates the MissilePixie
*/
void::MissilePixie::update() {
	/*float rads = this->getRotation().asRadians();
	double x = cos(rads);
	double y = sin(rads);
	if (abs(x) == 1) {
		this->move(Vector2f(y, x) * -MISSILE_SPEED);
	}
	else if (abs(x) != 1 && abs(y) != 1) {
		if (to_string(x * -1) == to_string(y)) {
			this->move(Vector2f(x, y * -1) * -MISSILE_SPEED);
		}
		else if (to_string(x) == to_string(y)) {
			this->move(Vector2f(x, y * -1) * MISSILE_SPEED);
		}
	}
	else {
		this->move(Vector2f(y, x) * MISSILE_SPEED);
	}*/

	float degs = this->getRotation().asDegrees(); // Get the MissilePixie's angle as degrees 
	//float degs = rads * 180 / 3.14159265f; // 
	float rads = degrees(degs+90).asRadians(); // Add a 90 deg offset
	float offsetX = std::cos(rads) * -speed; // Convert the unit vector coordinates to a normalized vector with the magnitude of the PixieMissile's speed
	float offsetY = std::sin(rads) * -speed;
	this->move(offsetX, offsetY); // Move the PixieMissile by the create offsets
}

/*
* remove()
* Params: None
* Returns: None
* Desc: Deletes the MissilePixie
*/
void MissilePixie::remove() {
	int id = this->getPixieID(); // Get the ID of the MissilePixie
	owner->missiles.erase(std::remove(owner->missiles.begin(), owner->missiles.end(), id), owner->missiles.end()); // Remove the MissilePixie from the active Missiles vector
	Pixie::removePixieByID(id); // Remove the Pixie
	owner->activeMissileCount--; // deinrement the active missile count
}

/*
* checkForCollision()
* Params: None
* Returns: bool
* Desc: Check if the MissilePixie is colliding with any other Pixie
*/
bool MissilePixie::checkCollision() {
	for (const auto& pixie : Pixie::pixies) { // Incrememnt throug the active Pixie vector
		if (this->getPixieID() != pixie->getPixieID() && pixie->getPixieID() != owner->getPixieID()) { // Check if the Pixie does not equal it's originator or itself
			if (this->isCollidingWith(*pixie)) { // Check if the two Pixie's are colliding
				return true;
			}
		}
	}
	return false;
}

/*
* checkForCollisions()
* Params: None
* Returns: None
* Desc: Check if there are any Pixies colliding with the MissilePixie, if so delete them and the MissilePixie
*/
void MissilePixie::checkForCollisions() {
	{
		if (Pixie::getPixieByID(owner->getPixieID()) == nullptr) { // Check if the originator exists
			return;
		}
		for (const auto& pixie : Pixie::pixies) { // Iterate through the active Pixies
			if (pixie == nullptr || pixie->sprite == nullptr || pixie == NULL || pixie->sprite == NULL) { // Check if the Pixie exists
				continue;
			}
			int pixieType = pixie->getPixieType(); // Get the Pixie type
			if (this->getPixieID() != pixie->getPixieID() && pixie->getPixieID() != owner->getPixieID() && pixie->pixieType != PIXIE_TYPE_BACKGROUND) { // Check if the Pixie is not itself, not the owner, and not the background
				if (this->isCollidingWith(*pixie)) { // Check if the two Pixies are colliding
					shared_ptr<ExplosionPixie> exp = ExplosionPixie::create(3, DEFAULT_EXPLOSION_TEXTURE, this->sprite->getPosition()); // Create an ExplostionPixie
					if (pixieType == PIXIE_TYPE_ENEMY) { // If the Pixie is an Enemy Pixie
						/*shared_ptr<EnemyPixie> enemy = std::dynamic_pointer_cast<EnemyPixie>(pixie);
						if (enemy) {
							if (bool died = enemy->damagePixie(damage)) {
								if (this->owner->getPixieType() == 1) {
									playerScore += 100;
								}
							}
						}*/
					}
					this->remove(); // Remove the Missile Pixie
					break; // Stop the loop
				}
			}
		}
	}
}

// Getters and Setters

/*
* getMissileByID(int id)
* Params: None
* Returns: shared_ptr<MissilePixie>
* Desc: Get the MissilePixie by its ID
*/
shared_ptr<MissilePixie> MissilePixie::getMissileByID(int id) {
	for (const auto& pixie : Pixie::pixies) { // Iterate through the active Pixie vector
		if (pixie->getPixieID() == id) { // Check if the Pixies have the same IDs
			return std::dynamic_pointer_cast<MissilePixie>(pixie); // Morph the Pixie into a MissilePixie and return it
		}
	}
	return nullptr;
}
