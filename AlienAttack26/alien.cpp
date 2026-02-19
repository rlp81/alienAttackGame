#include "gameHeader.h"

int Alien::alienCount = 0;
int Alien::totalAliens = 0;
Alien::Alien()
{
	name = "Alien";
	health = 10;
	damage = 10;
	faction = "Zorg";
	this->speed = DEFAULT_ALIEN_SPEED;
	alienTexture = loadTexture(DEFAULT_ENEMY_TEXTURE);
	Sprite* alien = new sf::Sprite(alienTexture);
	alien->setScale({ DEFAULT_ALIEN_SCALE, DEFAULT_ALIEN_SCALE });
	this->alienSprite = alien;
	alienCount++;
	totalAliens++;
	alienID = totalAliens;
}

Alien::Alien(string name)
{
	name = name;
	health = 10;
	damage = 10;
	faction = "Zorg";
	this->speed = DEFAULT_ALIEN_SPEED;
	alienTexture = loadTexture(DEFAULT_ENEMY_TEXTURE);
	Sprite* alien = new sf::Sprite(alienTexture);
	alien->setScale({ DEFAULT_ALIEN_SCALE, DEFAULT_ALIEN_SCALE });
	this->alienSprite = alien;
	alienCount++;
	totalAliens++;
	alienID = totalAliens;

}

Alien::Alien(string name, double health, double damage, float speed, string alienFileName, string faction) {
	this->name = name;
	this->health = health;
	this->damage = damage;
	this->alienFileName = alienFileName;
	this->faction = faction;
	this->alienTexture = loadTexture(alienFileName);
	Sprite* alien = new sf::Sprite(alienTexture);
	alien->setScale({ DEFAULT_ALIEN_SCALE, DEFAULT_ALIEN_SCALE });
	this->alienSprite = alien;
	this->speed = speed;
	alienCount++;
	totalAliens++;
	alienID = totalAliens;
};

void Alien::setPosition(float x, float y) {
	alienSprite->setPosition({x,y});
}

Alien::~Alien() {
	cout << "Alien " << name << " has been destroyed. \n";
	alienCount--;
	delete alienSprite;
}

void Alien::die() {
	if (health <= 0) {
		return;
	}
	cout << "dead\n";
	health = 0;
	aliens.erase(remove(aliens.begin(), aliens.end(), this), aliens.end());

	delete this;
}