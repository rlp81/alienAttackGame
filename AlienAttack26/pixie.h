#pragma once
#include "gameHeader.h"

const float DEFAULT_PIXIE_SPEED = 5.0f;
const float DEFAULT_PIXIE_SCALE = 1.5f;
const int DEFAULT_PIXIE_HEALTH = 10;
const int DEFAULT_PLAYER_AMMO = 99;
const float DEFAULT_MISSILE_SPEED = 6.0f;
const int DEFAULT_FRAMES_TILL__NEXT_MISSILE = 90;
const int MAX_ACTIVE_MISSILES = 3;

class Pixie {
private:
	friend class PlayerPixie;
	friend class EnemyPixie;
	friend class MissilePixie;
	friend class BackgroundPixie;
	static int pixieCount;
	static vector<std::shared_ptr<Pixie>> pixies;
	static vector<int> deletedPixies;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int pixieType;
	static int nextPixieID;
	int pixieID;
	float speed;
	bool active;
public:
	static shared_ptr<Pixie> create(int type, const std::string& textureFile);
	static shared_ptr<Pixie> create(int type, const std::string& textureFile, bool useOriginalOrigin);
	Pixie() = delete;
	Pixie(int type, const std::string& textureFile);
	Pixie(int type, const std::string& textureFile, bool useOriginalOrigin);
	//~Pixie();
	virtual ~Pixie() = default;
	bool isOffScreen() const;
	void draw(sf::RenderWindow& window);
	int getPixieType() const { return pixieType; }
	int getPixieID() const { return pixieID; }
	static int getPixieCount() { return pixieCount; }
	float getSpeed() const { return speed; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	bool checkIfActive();
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
	static void drawAll(sf::RenderWindow& window);
	static void deleteOld();
};

class PlayerPixie : public Pixie {
private:
	friend class MissilePixie;
	int ammo;
	int health;
	int activeMissileCount;
	float direction;
	int lastMissileFrame;
	//vector<MissilePixie*> missiles;
	vector<int> missiles;
public:
	PlayerPixie();
	void shootMissile();
	void update();
	void updateMissiles();
	static shared_ptr<PlayerPixie> create();
};

class EnemyPixie : public Pixie {};

class MissilePixie : public Pixie {
private:
	PlayerPixie* owner;
	float direction;
public:
	MissilePixie(PlayerPixie* owner);
	virtual ~MissilePixie() = default;
	void update();
	bool checkCollision();
	static shared_ptr<MissilePixie> getMissileByID(int id);
	void remove();
	static shared_ptr<MissilePixie> create(PlayerPixie* owner);
};


class BackgroundPixie : public Pixie {
public:
	BackgroundPixie(const std::string& textureFile) : Pixie(0, textureFile, true) {
		setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	}
	static shared_ptr<BackgroundPixie> create(string textureFile) {
		auto pixie = make_shared<BackgroundPixie>(textureFile);
		pixies.push_back(pixie);
		return pixie;
	}
};