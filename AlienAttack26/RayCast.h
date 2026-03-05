#pragma once
#include "gameHeader.h"

class RayCast {
private:
	sf::Vector2f origin;
	sf::Vector2f position;
	sf::Angle direction;
	int resultId;
	int speed;
	float traveled;
	vector<int> ignoreList;
	bool hit;
	bool offScreen;
public:
	RayCast() = delete;
	RayCast(sf::Vector2f origin, sf::Angle direction);
	RayCast(Vector2f origin, Angle direction, vector<int> &ignoreList);
	int getResultID() { return resultId; }
	bool isHit() { return hit; }
	bool isOffScreen() { return offScreen; }
	sf::Vector2f getPosition() { return position; }

};