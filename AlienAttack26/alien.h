#pragma once
#include "gameHeader.h"

const float DEFAULT_ALIEN_SPEED = 3.0f;
const float DEFAULT_ALIEN_SCALE = 1.5f;

class Alien {
private:
	static int totalAliens;
	int alienID;
	string name;
	double health;
	double damage;
	string alienFileName;
	string faction;
	float speed;
	sf::Texture alienTexture;
public:
	static int alienCount;
	sf::Sprite* alienSprite;
	string getName() { return name; }
	double getHealth() { return health; }
	double getDamage() { return damage; }
	string getFaction() { return faction; }
	void setName(string newName) { name = newName; }
	void setHealth(int newHealth) { health = newHealth; }
	void setDamage(int newDamage) { damage = newDamage; }
	void setFaction(string newFaction) { faction = newFaction; }
	void die();
	void setPosition(float x, float y);
	float getSpeed() { return speed; }
	int getID() { return alienID; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	Alien();
	Alien(string name);
	Alien(string name, double health, double damage, float speed, string alienFileName, string faction);
	~Alien();
};
