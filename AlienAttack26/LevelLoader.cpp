#include "gameHeader.h"

LevelLoader::LevelLoader() {
	level = 0;
	player = nullptr;
	loaded = false;
}

void LevelLoader::clearLevel() {
	loaded = false;
	Pixie::pixies.clear(); // Clear the vector of pixies to remove all existing pixies from the level
	Pixie::nextPixieID = 0; // Reset the next Pixie ID to 0
}

void LevelLoader::loadLevel() {
	clearLevel(); // Clear the level of all existing pixies
	srand(time(0));
	int lastLevel = level++; // Increment the level
	int enemiesPerSwarm = 2 + (rand() % level);
	currentFrame = 0; // Reset the current frame to 0 for the new level
	loadDefaults(); // Load the default pixies for the level, such as the background and player pixie
	loadEnemies(level, enemiesPerSwarm); // Load the enemies for the level, the amount of swarms and enemies per swarm is based on the current level
	loaded = true; // Set the level to be loaded
}

void LevelLoader::loadDefaults() {
	shared_ptr<BackgroundPixie> background = BackgroundPixie::create(DEFAULT_BACKGROUND_TEXTURE); // set the background of the game
	background->setPosition({ 0, 0 }); // set the position of the background

	shared_ptr<PlayerPixie> playerPixie = PlayerPixie::create(); // Create the spaceship the player will use and control
	playerPixie->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f }); // set the position of the player spaceship to the center of the screen
	this->player = playerPixie; // Set the player variable to the created player pixie

}

void LevelLoader::loadEnemies(int swarms, int enemiesPerSwarm) {
	if (swarms <= 0 || enemiesPerSwarm <= 0)
		throw invalid_argument("Swarms and enemies per swarm must be greater than 0"); // Check if the amount of swarms and enemies per swarm is valid, throw an error if not
	for (int i = 0; i < swarms; i++) {
		vector<int> swarmMembers; // Create a vector for enemy pixie IDs that will be controlled
		shared_ptr<EnemyPixie> leader = EnemyPixie::create(playerID); // Create the leader of the swarm
		leader->setPosition(300, 300); // set the position of the leader to 300,300
		leader->setPattern(2);

		shared_ptr<EnemyPixie> enemy; // Make the generic enemy pixie variable to store each member created and placed into the swarm
		swarmMembers.push_back(leader->getPixieID()); // place the leader into the swarm vector
		for (int i = 0; i < enemiesPerSwarm; i++) { // create 6 enemy pixies
			enemy = EnemyPixie::create(playerID); // Create a new enemy pixie and set the player as its target
			if (i % 2 == 0) { // Check if the pixie is an even or odd number in the loop
				enemy->changeOrbitDirection(); // Change the orbit direction if it is even
			}
			swarmMembers.push_back(enemy->getPixieID()); // place the enemy pixie's ID into the swarm vector
		}

		Swarm::create(leader->getPixieID(), swarmMembers); // Create the swarm class with the leader's ID and the vector of the swarm member IDs
	}
}

void LevelLoader::updateLevel() {
	if (!loaded)
		throw runtime_error("Level is not loaded, cannot update level"); // Check if the level is loaded, throw an error if it is not
	player->update(); // Update the player pixie
	ExplosionPixie::updateAll(); // Update all the explosion pixies
	Swarm::updateAllSwarms(); // Update all the swarms, this will update the leaders and all members of the swarms
	if (Swarm::getTotalEnemyCount() <= 0) { // Check if there are no more enemies in the level
		loaded = false;
		loadLevel(); // Load the next level if there are no more enemies
	}
}

void LevelLoader::checkForWindowEvents(RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) { // Check if an event has occured
		if (event->is<sf::Event::Closed>()) { // check if the event was closing the window
			window.close(); // Close the window
		}
	}
}