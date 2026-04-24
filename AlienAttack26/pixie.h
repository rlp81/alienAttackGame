#pragma once
#include "gameHeader.h"
/*
* pixie.h
* Description: Header file for the Pixie Class and it's related constants
* Author: Cole Lehl
*/

// Constants
const float DEFAULT_PIXIE_SPEED = 5.0f; // Default pixie speed
const float DEFAULT_PIXIE_SCALE = 1.5f; // Default pixie scale
const int DEFAULT_PIXIE_HEALTH = 10; // Default pixie health
const int DEFAULT_PLAYER_AMMO = 99; // Default player ammo
const float DEFAULT_MISSILE_SPEED = 6.0f; // Default missile speed
const int DEFAULT_FRAMES_TILL_NEXT_MISSILE = 90; // Default frames until a ShipPixie can fire another missile
const int MAX_ACTIVE_MISSILES = 4; // Max active missiles for a given ShipPixie

// Constants - Pixie Types
const int PIXIE_TYPE_BACKGROUND = 0; // ID For a Pixie Background
const int PIXIE_TYPE_PLAYER_SHIP = 1; // ID For a Player Controlled Ship Pixie
const int PIXIE_TYPE_MISSILE = 2; // ID For a Missile Pixie
const int PIXIE_TYPE_ENEMY = 3; // ID For an Enemy Controlled Ship Pixie
const int PIXIE_TYPE_EXPLOSION = 4; // ID For an Explosion Pixie

// Main Pixie Class,Offers a useful frontend for the sf::Sprite class and is the parent class for all other Pixie types
class Pixie {
private:
	// Friend children; Pixies are designed to act as though they are all part of the same class
	friend class ShipPixie;
	friend class PlayerPixie;
	friend class EnemyPixie;
	friend class MissilePixie;
	friend class BackgroundPixie;
	friend class ExplosionPixie;
	friend class LevelLoader; // Friend the level loader so it can access private members of the Pixie class to load and clear levels

	// Friend Swarm, a default built-in controller for Enemy Pixies
	friend class Swarm;
	
	// Static Variables
	static int pixieCount; // Current Pixie count
	static map<int, shared_ptr<Pixie>> pixies; // Vector of all existing pixies
	static int nextPixieID; // Next ID for a created Pixie

	// Pointers
	sf::Texture* texture; // Texture pointer to store the texture of the pixie
	sf::Sprite* sprite; // Sprite Pointer to store the sprite of the pixie

	// Pixie Variables
	int pixieType; // Type of Pixie
	int pixieID; // ID of Pixie
	float speed; // Speed of pixie
	bool active; // Is the Pixie active
public:
	// Constructors
	static shared_ptr<Pixie> create(int type, const std::string& textureFile); // Static function to create a Pixie and add it to the vector of pixies
	static shared_ptr<Pixie> create(int type, const std::string& textureFile, bool useOriginalOrigin); // Identical function, but allows the Pixie to use the original origin (0,0)

	Pixie() = delete; // Delete the default constructor, all pixies are created with a type and/or texture
	Pixie(int type); // Create a Pixie with only a type
	Pixie(int type, const std::string& textureFile); // Create a Pixie with both a type and a texture
	Pixie(int type, const std::string& textureFile, bool useOriginalOrigin); // Create a Pixie with a type, texture, and allows the Pixie to use the original origin (0,0)
	// Use the default Destructor and allow Shared pointer logic to handle the destruction of Pixies
	virtual ~Pixie();
	
	// Static Functions
	static shared_ptr<Pixie> getPixieByID(int ID); // return a shared pointer of a Pixie by the ID associated with it
	static void removePixieByID(int ID); // Remove a Pixie using it's ID
	static int pixieAtPosition(Vector2f pos); // Find a Pixie at a given position, returns the ID of the Pixie if found, otherwise returns -1
	static int getPixieCount() { return pixieCount; } // Get the amount of Pixies currently in existence
	static void drawAll(sf::RenderWindow& window); // Drawl all existing pixies onto the window

	// Logic Functions
	bool isOffScreen() const; // Check if the Pixie is off the screen
	void draw(sf::RenderWindow& window); // Draw the pixie to the window

	// Getters and Setters
	int getPixieType() const { return pixieType; } // Get the type of Pixie
	int getPixieID() const { return pixieID; } // Get the ID of the Pixie
	float getSpeed() const { return speed; } // Get the speed of the Pixie
	void setSpeed(float newSpeed) { speed = newSpeed; } // Set the speed of the Pixie
	void setPosition(float x, float y) { // Set the position of the Pixie using x and y coordinates
		if (sprite) {
			sprite->setPosition({ x, y });
		}
	}
	void setPosition(sf::Vector2f pos) { // Set the position of the Pixie using a Vector2f
		if (sprite) {
			sprite->setPosition(pos);
		}
	}
	sf::Vector2f getPosition() const { // Get the position of the Pixie, returns a Vector2f
		if (sprite) {
			return sprite->getPosition();
		}
		return sf::Vector2f(0, 0);
	}
	sf::Vector2f getScale() const { // Get the scale of the Pixie's Sprite, returns a Vector2f
		if (sprite) {
			return sprite->getScale();
		}
		return sf::Vector2f(0, 0);
	}
	void setScale(float x, float y) { // Set the scale of the Pixie's Sprite using x and y coordinates
		if (sprite) {
			sprite->setScale({ x, y });
		}
	}
	bool isCollidingWith(const Pixie& other) const; // Check if the Pixie is colliding with another given Pixie
	float getDirectionTo(const Pixie& other); // Get the direction to a another given pixie, returns a Radian angle
	void move(float dx, float dy) { // Move the Pixie's Sprite by a given x and y offset
		if (sprite) {
			sprite->move({ dx, dy });
		}
	}
	void move(const sf::Vector2f& offset) { // Move the Pixie's Sprite by a given offset Vector2f
		if (sprite) {
			sprite->move(offset);
		}
	}
	sf::Angle getRotation() const { // Get the Angle of a Pixie's Sprite as an Angle object
		if (sprite) {
			return sprite->getRotation();
		}
		return sf::Angle();
	}
	void setRotation(sf::Angle angle) { // Set the Angle of a Pixie's Sprite using an Angle object
		if (sprite) {
			sprite->setRotation(angle);
		}
	}
};
