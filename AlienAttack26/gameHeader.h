#pragma once
/*
*  gameFunctions.cpp
*     - The functions for the game program are in this file.
*
*  AUTHOR: Most of the work in this program was completed by Prof. Andy Harbert
*          Prof. Pat Smith has made modifications (December 2021)
*			Cole Lehl has made modifications (January 2026)
*
*/
// C++ Libraries
#include <iostream>
#include <vector>
#include <memory>
using namespace std; // Use the standard namespace

// SFML Graphics Library
#include <SFML/Graphics.hpp> // Basic graphic library

using namespace sf; // Use the SFML namespace

#include "pixie.h" // Basic Pixie Class
#include "PixieShip.h" // Basic Ship Pixie/Controllable Class | Parent: Pixie
#include "PixieBackground.h" // Background Pixie Class | Parent: Pixie
#include "PixieEnemy.h" // Enemy Pixie Class | Parent: PixieShip
#include "PixieMissile.h" // Missile Pixie Class | Parent: Pixie
#include "PixiePlayer.h" // Player Pixie Class | Parent: PixieShip
#include "ExplosionPixie.h" // Explosion Pixie Class | Parent: Pixie
#include "Swarm.h" // Swarm Class to control Enemy Pixies
#include "RayCast.h" // Raycast Class to handle occlusion and line of sight for the enemy pixies
#include "LevelLoader.h"
enable_shared_from_this<Pixie>; // Enable the use of shared pointers for the Pixie class and its children

// Main Constants
const float DISTANCE = 5.0f; // Basic Pixie movement distance 
const float MISSILE_SPEED = 10.0f; // When the missile moves it moves 10 pixels at a time.
const int WINDOW_WIDTH = 800; // window is 800 pixels wide
const int WINDOW_HEIGHT = 600;// window is 600 pixels vertically "high"
const string DEFAULT_ENEMY_TEXTURE = "enemy.bmp"; // Default Enemy Texture file name
const string DEFAULT_SHIP_TEXTURE = "ship.bmp"; // Default Player Ship Texture file name
const string DEFAULT_MISSILE_TEXTURE = "missile.png"; // Default Missile Texture file name
const string DEFAULT_BACKGROUND_TEXTURE = "stars.jpg"; // Default Background Texture file name
const int DUMP_PIXIES_EVERY = 120; // Deprecated constant TODO: DELETE THIS
extern int lastPixieDumpFrame; // Deprecated constant
extern int currentFrame; // Current window frame displayed to the user
extern int playerScore; // Current player score, unused
extern int playerID; // The player's PixieID


// Game Functions
void updateShip(Sprite& ship); // Deprecated function, TODO: DELETE THIS
Vector2f getSpriteTopCenterPosition(const Sprite& sprite); // Get the top center position of a sprite
void setSpriteCenterPosition(Sprite& sprite, Vector2f centerPosition); // Set the origin of a sprite
Vector2f getSpriteCenterPosition(const Sprite& sprite); // Get center position of a sprite
bool isSpriteOffScreen(const Sprite& sprite); // Check if a sprite is off screen
Vector2f getSpriteCenter(const Sprite& sprite); // Get center position of a sprite
Texture loadTexture(const string& fileName); // Load the texture of a sprite, deprecated
bool checkCollision(const Sprite& sprite1, const Sprite& sprite2); // Check if two sprites are colliding, Deprecated
