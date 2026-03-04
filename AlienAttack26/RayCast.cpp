#include "gameHeader.h"

RayCast::RayCast(Vector2f origin, Angle direction) {
	this->origin = origin;
	cout << "RayCast origin: " << origin.x << ", " << origin.y << endl;
	this->direction = direction;
	this->position = origin;
	speed = 1.5;
	hit = false;
	offScreen = false;
	float rads = direction.asRadians();
	float offsetX = cos(rads) * speed;
	float offsetY = sin(rads) * speed;
	int foundID;
	while (hit == false && offScreen == false) {
		position.x += offsetX;
		position.y += offsetY;
		cout << "RayCast position: " << position.x << ", " << position.y << endl;
		foundID = Pixie::pixieAtPosition(position);
		if (foundID != -1) {
			resultId = foundID;
			hit = true;
		}
		else {
			if (position.x > WINDOW_WIDTH || position.x < 0 || position.y > WINDOW_HEIGHT || position.y < 0) {
				offScreen = true;
			}
		}
	}
}

RayCast::RayCast(Vector2f origin, Angle direction, vector<int>& ignoreList) {
	this->origin = origin;
	cout << "RayCast origin: " << origin.x << ", " << origin.y << endl;
	this->direction = direction;
	this->position = origin;
	speed = 1.5;
	hit = false;
	offScreen = false;
	float rads = direction.asRadians();
	float offsetX = cos(rads) * speed;
	float offsetY = sin(rads) * speed;
	int foundID;
	while (hit == false && offScreen == false) {
		position.x += offsetX;
		position.y += offsetY;
		cout << "RayCast position: " << position.x << ", " << position.y << endl;
		foundID = Pixie::pixieAtPosition(position);
		if (foundID != -1) {
			for (int id : ignoreList) {
				if (id == foundID) {
					foundID = -1;
					break;
				}
			}
			if (foundID != -1) {
				resultId = foundID;
				hit = true;
			}
		}
		else {
			if (position.x > WINDOW_WIDTH || position.x < 0 || position.y > WINDOW_HEIGHT || position.y < 0) {
				offScreen = true;
			}
		}
	}
}