#pragma once
#include "gameHeader.h"

const float DEFAULT_PIXIE_SPEED = 5.0f;
const float DEFAULT_PIXIE_SCALE = 1.5f;

class Pixie {
private:
	static int pixieCount;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int pixieType;
	static int nextPixieID;
	int pixieID;
	float speed;
public:
	Pixie() = delete; // Default constructor is deleted to enforce type and texture initialization
	Pixie(int type, const std::string& textureFile);
	virtual ~Pixie() = default;
	int getPixieType() const { return pixieType; }
	int getPixieID() const { return pixieID; }
	float getSpeed() const { return speed; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y) {
		if (sprite) {
			sprite->setPosition({ x, y });
		}
	}
	Vector2f getPosition() const {
		if (sprite) {
			return sprite->getPosition();
		}
		return Vector2f(0, 0);
	}
};
class PlayerPixie : public Pixie {};
class EnemyPixie : public Pixie {};
class MissilePixie : public Pixie {};