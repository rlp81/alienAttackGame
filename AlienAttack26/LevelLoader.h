#pragma once
#include "gameHeader.h"

struct EnemyModifier {
	int healthModifier;
	double speedModifier;
	double damageModifier;
	int ammoModifier;
};

struct PlayerModifier {
	int healthModifier;
	double speedModifier;
	double damageModifier;
	int ammoModifier;
};

class LevelLoader {
private:
	bool loaded;
	int enemyCount;
	int swarmCount;
	int level;
	shared_ptr<PlayerPixie> player;
	EnemyModifier enemyModifier;
	PlayerModifier playerModifier;
	void loadDefaults();
	void loadEnemies(int swarms, int enemiesPerSwarm);
public:
	bool isLoaded() const { return loaded; }
	static void checkForWindowEvents(RenderWindow& window);
	LevelLoader();
	void loadLevel();
	void clearLevel();
	void updateLevel();
};