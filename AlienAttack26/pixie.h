#pragma once
#include "gameHeader.h"

const float DEFAULT_PIXIE_SPEED = 5.0f;
const float DEFAULT_PIXIE_SCALE = 1.5f;
const int DEFAULT_PIXIE_HEALTH = 10;
const int DEFAULT_PLAYER_AMMO = 99;
const int DEFAULT_MISSILE_SPEED = 6.0f;


class Pixie {
private:
	friend class PlayerPixie;
	friend class EnemyPixie;
	friend class MissilePixie;
	static int pixieCount;
	static vector<Pixie*> pixies;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int pixieType;
	static int nextPixieID;
	int pixieID;
	float speed;
public:
	Pixie() = delete;
	Pixie(int type, const std::string& textureFile);
	virtual ~Pixie() = default;
	bool isOffScreen() const;
	void draw(sf::RenderWindow& window);
	int getPixieType() const { return pixieType; }
	int getPixieID() const { return pixieID; }
	static int getPixieCount() { return pixieCount; }
	float getSpeed() const { return speed; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	void setPosition(float x, float y) {
		if (sprite) {
			sprite->setPosition({ x, y });
		}
	}
	void setPosition(sf::Vector2f pos) {
		if (sprite) {
			sprite->setPosition(pos);
		}
	}
	sf::Vector2f getPosition() const {
		if (sprite) {
			return sprite->getPosition();
		}
		return sf::Vector2f(0, 0);
	}
	sf::Vector2f getScale() const {
		if (sprite) {
			return sprite->getScale();
		}
		return sf::Vector2f(0, 0);
	}
	void setScale(float x, float y) {
		if (sprite) {
			sprite->setScale({ x, y });
		}
	}
	bool isCollidingWith(const Pixie& other) const;
	void move(float dx, float dy) {
		if (sprite) {
			sprite->move({ dx, dy });
		}
	}
	void move(const sf::Vector2f& offset) {
		if (sprite) {
			sprite->move(offset);
		}
	}
	sf::Angle getRotation() const {
		if (sprite) {
			return sprite->getRotation();
		}
		return sf::Angle();
	}
	void setRotation(sf::Angle angle) {
		if (sprite) {
			sprite->setRotation(angle);
		}
	}
};

class PlayerPixie : public Pixie {
private:
	friend class MissilePixie;
	int ammo;
	int health;
	int activeMissileCount;
	vector<MissilePixie*> missiles;
public:
	PlayerPixie();
	void shootMissile();
	void update();
	void updateMissiles(RenderWindow& window);
};
class EnemyPixie : public Pixie {};
class MissilePixie : public Pixie {
private:
	PlayerPixie* owner;
	Angle direction;
public:
	MissilePixie(PlayerPixie* owner);
	virtual ~MissilePixie() = default;
	void update();
	bool checkCollision();
};