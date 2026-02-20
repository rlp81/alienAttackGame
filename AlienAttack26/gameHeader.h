#pragma once
/*
*  gameFunctions.cpp
*     - The functions for the game program are in this file.
*
*  AUTHOR: Most of the work in this program was completed by Prof. Andy Harbert
*          Prof. Pat Smith has made modifications (December 2021)
*
*/
// includes go below
#include <iostream>
#include <vector>
using namespace std;
// these two lines are specific to the SFML graphics library. 
#include <SFML/Graphics.hpp>
//#include "alien.h"
#include "pixie.h"
#include <memory>
using namespace sf;
enable_shared_from_this<Pixie>;

// Constants for the game 
const float DISTANCE = 5.0f; // When the ship moves it moves 5 pixels at a time. 
const float MISSILE_SPEED = 10.0f; // When the missile moves it moves 10 pixels at a time.
const int WINDOW_WIDTH = 800; // window is 800 pixels wide
const int WINDOW_HEIGHT = 600;// window is 600 pixels vertically "high"
const string DEFAULT_ENEMY_TEXTURE = "enemy.bmp";
const string DEFAULT_SHIP_TEXTURE = "ship.bmp";
const string DEFAULT_MISSILE_TEXTURE = "missile.png";
const string DEFAULT_BACKGROUND_TEXTURE = "stars.jpg";
const int DUMP_PIXIES_EVERY = 120;
extern int lastPixieDumpFrame;
extern int currentFrame;


// Game Functions
void updateShip(Sprite& ship);
Vector2f getSpriteTopCenterPosition(const Sprite& sprite);
void setSpriteCenterPosition(Sprite& sprite, Vector2f centerPosition);
Vector2f getSpriteCenterPosition(const Sprite& sprite);
bool isSpriteOffScreen(const Sprite& sprite);
Vector2f getSpriteCenter(const Sprite& sprite);
Texture loadTexture(const string& fileName);
bool checkCollision(const Sprite& sprite1, const Sprite& sprite2);
//void newAlien();
