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
	shared_ptr<BackgroundPixie> background = BackgroundPixie::create(DEFAULT_BACKGROUND_TEXTURE); // set the background of the game
	background->setPosition({ 0, 0 }); // set the position of the background

	shared_ptr<PlayerPixie> playerPixie = PlayerPixie::create(); // Create the spaceship the player will use and control
	playerPixie->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f }); // set the position of the player spaceship to the center of the screen

	vector<int> swarmMembers; // Create a vector for enemy pixie IDs that will be controlled
	shared_ptr<EnemyPixie> leader = EnemyPixie::create(playerPixie->getPixieID()); // Create the leader of the swarm
	leader->setPosition(300, 300); // set the position of the leader to 300,300
	leader->setPattern(2);
	srand(time(0)); // Seed the random number generator with the current time

	shared_ptr<EnemyPixie> enemy; // Make the generic enemy pixie variable to store each member created and placed into the swarm
	swarmMembers.push_back(leader->getPixieID()); // place the leader into the swarm vector
	for (int i = 0; i < 6; i++) { // create 6 enemy pixies
		enemy = EnemyPixie::create(playerPixie->getPixieID()); // Create a new enemy pixie and set the player as its target
		if (i % 2 == 0) { // Check if the pixie is an even or odd number in the loop
			enemy->changeOrbitDirection(); // Change the orbit direction if it is even
		}
		swarmMembers.push_back(enemy->getPixieID()); // place the enemy pixie's ID into the swarm vector
	}

	Swarm swarm = Swarm(leader->getPixieID(), swarmMembers); // Create the swarm class with the leader's ID and the vector of the swarm member IDs
	
	// Main Game loop that runs while the window is open
	while (window.isOpen()) {
		currentFrame++; // at every frame interate the current frame by 1
		while (const std::optional event = window.pollEvent()){ // Check if an event has occured
			if (event->is<sf::Event::Closed>()) { // check if the event was closing the window
				window.close(); // Close the window
			}
		}
		 
		playerPixie->update(); // Update the player pixie
		swarm.updateSwarm(); // Update the swarm, this will update the leader and all members of the swarm
		ExplosionPixie::updateAll(); // Update all the explosion pixies
		window.clear(); // Clear the old frame before this frame
		Pixie::drawAll(window); // Draw the new frame
		window.display(); // Display the new frame
	}
}