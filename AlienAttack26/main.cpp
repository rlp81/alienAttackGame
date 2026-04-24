#include "gameHeader.h"

/*
* main.cpp
* Description: Main File for Generic Alien Attack Game 2026 Edition, this file calls the main game loop and handles the basic events and functions
* Author: Cole Lehl
*/
int currentFrame = 0; // Current window frame displayed to the user

int main() {
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!"); // Initialize the game window
	window.setFramerateLimit(60); // set the game framerate limit to 60 frames per second
	LevelLoader levelLoader; // Create a level loader to load the levels of the game
	levelLoader.loadLevel(); // Load the first level of the game

	// Main Game loop that runs while the window is open
	while (window.isOpen()) {
		currentFrame++; // at every frame interate the current frame by 1
		LevelLoader::checkForWindowEvents(window); // Check for window events such as closing the window or resizing the window
		if (levelLoader.isLoaded()) {
			levelLoader.updateLevel(); // Update the level, this will update all the pixies in the level and handle their interactions
		}
		window.clear(); // Clear the old frame before this frame
		Pixie::drawAll(window); // Draw the new frame
		UI_Controller->draw(window);
		DisposableText::drawAll(window);
		window.display(); // Display the new frame
	}
}