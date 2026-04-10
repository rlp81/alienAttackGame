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
	int enemyCount;
	int swarmCount;
	int level;
	EnemyModifier enemyModifier;
	PlayerModifier playerModifier;
public:
	LevelLoader();
	void loadLevel();
	void clearLevel();

};
