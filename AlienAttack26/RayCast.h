#pragma once
#include "gameHeader.h"

class RayCast {
private:
	Vector2f origin;
	Vector2f position;
	Angle direction;
	int resultId;
	int speed;
	bool hit;
	bool isOffScreen;
public:
	RayCast() = delete;
	RayCast(Vector2f origin, Angle direction);
	RayCast(Vector2f origin, Angle direction, vector<int> &ignoreList);

};