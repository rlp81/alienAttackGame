#include "gameHeader.h"
Alien::Alien()
{
	name = "Alien";
	health = 100;
	damage = 10;
	faction = "Zorg";
	alienTexture = loadTexture(DEFAULT_ENEMY_TEXTURE);
	this->alienSprite = new sf::Sprite(alienTexture);
}
Alien::Alien(string name, double health, double damage, string alienFileName, string faction) {
	this->name = name;
	this->health = health;
	this->damage = damage;
	this->alienFileName = alienFileName;
	this->faction = faction;
	this->alienTexture = loadTexture(alienFileName);
	this->alienSprite = new sf::Sprite(alienTexture);
};
void Alien::setPosition(float x, float y) {
	alienSprite->setPosition({x,y});
}
Alien::~Alien() {
	delete alienSprite;
}

void Alien::die() {
	health = 0;
	Alien::~Alien();
}