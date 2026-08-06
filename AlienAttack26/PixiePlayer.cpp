#include "gameHeader.h"
/*
* PixiePlayer.cpp
* Description: function C++ file for the PlayerPixie Class
* Author: Cole
*/

const int PLAYER_FRAME_UNTIL_MISSILE = 60; // The amount of frames that must pass before the Player can fire another missile

// Constructors

/*
* PlayerPixie()
* Params: None
* Returns: None
* Desc: Creates an PlayerPixie
*/
PlayerPixie::PlayerPixie() : ShipPixie(PIXIE_TYPE_PLAYER_SHIP, DEFAULT_SHIP_TEXTURE) {
	setSpeed(DEFAULT_PIXIE_SPEED);
	setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	ammo = 20;
	health = 10;
	damage = 1;
	direction = 0;
}

/*
* create()
* Params: None
* Returns: shared_ptr<PlayerPixie>
* Desc: Creates an PlayerPixie as a shared pointer and adds it to the active Pixies vector
*/
shared_ptr<PlayerPixie> PlayerPixie::create() {
	auto player = make_shared<PlayerPixie>(); // Create a PlayerPixie as a shared pointer
	pixies[player->pixieID] = player; // add the player to the active Pixies vector
	playerID = player->getPixieID(); // Set the global variable for the Player's ID to the PlayerPixie's ID
	return player; // Return the PlayerPixie
}

/*
* update()
* Params: None
* Returns: None
* Desc: Updates the PlayerPixie and check's for User input from the Keyboard
*/
void PlayerPixie::update()
{
	// The x and y rotation of the player
	int xRotation = 0; 
	int yRotation = 0;

	// Check if the left or A key were pressed
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		// left arrow is pressed: move our ship left by DISTANCE
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		yRotation = -90; // set the rotation to point to the left
		this->sprite->setRotation(degrees(yRotation)); // Set the PlayerPixie's sprite's rotation
		this->move({ -DISTANCE, 0 });  // Move to the left on the X axis
	}
	// Check iff the right or D key were pressed
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		// right arrow is pressed: move our ship right by DISTANCE
		yRotation = 90; // set the rotation to point to the right
		this->setRotation(degrees(90)); // Set the PlayerPixie's sprite's rotation
		this->move({ DISTANCE, 0 }); // Move to the right on the X axis
	}
	// Check if the up or W keys were pressed
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)) {
		xRotation = 1; // Set the vertical rotation to 1 to signify to move upwards
		this->setRotation(degrees(0)); // Set the PlayerPixie's sprite's rotation
		this->move({ 0.0, -DISTANCE }); // Move up by DISTANCE
	}
	// Check if the down or S keys were pressed
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)) {
		xRotation = -1; // Set the vertical rotation to -1 to signify to move downwards
		this->setRotation(degrees(180)); // Set the PlayerPixie's sprite's rotation
		this->move({ 0.0, DISTANCE }); // Move down by DISTANCE
	}
	// Check if the Space key was pressed
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		this->shootMissile(); // Shoot a missile from the PlayerPixie
	}

	// Check if the PlayerPixie is moving up or down
	if (xRotation != 0) {
		// Switch the current yrotaion
		switch (yRotation) {
		case -90: // If the yrotation is -90
			direction = -45; // Set the direction to -45 degs
			if (xRotation < 0) // if the ship is moving downwards
				direction = -135; // Set the direction to -135 degs
			break;
		case 90: // If the yRotation is 90
			direction = 45; // Set the direction to 45 degs
			if (xRotation < 0) // If the ship is moving upwards
				direction = 135; // Set the direction to 135 degs
			break;
		default: // If neither cases are met run the following
			switch (xRotation) // Switch the current xRotation
			{
			case(-1): // If moving downwards
				direction = 180; // Set direction to 180
				break;
			case(1): // If moving upwards
				direction = 0; // Set the direction to 0
				break;
			}
		}
	}
	else { // if the player is not moving upwards or downwards
		if (yRotation != 0) // Check if the yRotation is used
			direction = yRotation; // Set the direction to the yRotation
	}
	this->setRotation(degrees(direction)); // Set the PlayerPixie's Sprite's rotation to the result direction
}

/*
* shootMissile()
* Params: None
* Returns: None
* Desc: Shoots a missile in the direction the ShipPixie is facing
*/
void PlayerPixie::shootMissile() {
	if (!(currentFrame >= DEFAULT_FRAMES_TILL_NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) { // Check if the ShipPixie can fire a missile based on the current frame
		return;
	}
	//if (activeMissileCount >= MAX_ACTIVE_MISSILES) { // Check if there are max existing missiles
	//	return;
	//}
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
