#include "gameHeader.h"

RayCast::RayCast(Vector2f origin, Angle direction) {
	this->origin = origin;
	this->direction = direction;
	this->position = origin;
	speed = 1;
	hit = false;
	isOffScreen = false;
	float rads = direction.asRadians();
	float offsetX = cos(rads) * speed;
	float offsetY = sin(rads) * speed;
	int foundID;
	while (hit == false && isOffScreen == false) {
		position.x += offsetX;
		position.y += offsetY;
		foundID = Pixie::pixieAtPosition(position);
		if (foundID != -1) {
			resultId = foundID;
			hit = true;
		}
		else {
			if (position.x > WINDOW_WIDTH || position.x < 0 || position.y > WINDOW_HEIGHT || position.y < 0) {
				isOffScreen = true;
			}
		}
	}
}