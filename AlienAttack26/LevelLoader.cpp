#include "gameHeader.h"

LevelLoader::LevelLoader() {
	level = 0;
}

void LevelLoader::clearLevel() {
	Pixie::pixies.clear(); // Clear the vector of pixies to remove all existing pixies from the level
}

void LevelLoader::loadLevel() {
	int lastLevel = level++; // Increment the level
	clearLevel(); // Clear the level of all existing pixies

}