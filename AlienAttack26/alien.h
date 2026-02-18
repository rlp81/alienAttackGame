#pragma once
#include "gameHeader.h"

class Alien {
private:
	static int alienCount;
	string name;
	double health;
	double damage;
	string alienFileName;
	string faction;
	sf::Texture alienTexture;
public:
	sf::Sprite* alienSprite;
	string getName() { return name; }
	double getHealth() { return health; }
	double getDamage() { return damage; }
	string getFaction() { return faction; }
	void setName(string newName) { name = newName; }
	void setHealth(int newHealth) { health = newHealth; }
	void setDamage(int newDamage) { damage = newDamage; }
	void setFaction(string newFaction) { faction = newFaction; }
	Alien();
	Alien(string name, double health, double damage, string alienFileName, string faction);
	void die();
	void setPosition(float x, float y);
	~Alien();
};