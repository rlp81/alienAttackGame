#include "gameHeader.h"

PlayerPixie::PlayerPixie() : ShipPixie(PIXIE_TYPE_PLAYER_SHIP, DEFAULT_SHIP_TEXTURE) {
	setSpeed(DEFAULT_PIXIE_SPEED);
	setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	ammo = DEFAULT_PLAYER_AMMO;
	health = DEFAULT_PIXIE_HEALTH;
	damage = 10;
	direction = 0;
}

shared_ptr<PlayerPixie> PlayerPixie::create() {
	auto player = make_shared<PlayerPixie>();
	pixies.push_back(player);
	playerID = player->getPixieID();
	return player;
}

bool MissilePixie::


() {
	for (const auto& pixie : Pixie::pixies) {
		if (this->getPixieID() != pixie->getPixieID() && pixie->getPixieID() != owner->getPixieID()) {
			if (this->isCollidingWith(*pixie)) {
				return true;
			}
		}
	}
	return false;
}

void PlayerPixie::update()
{
	/*
	 *  This first If-then-else-if Block handles
	 */
	int xRotation = 0;
	int yRotation = 0;

	/*
	 *  This first If-then-else-if Block handles
	 */
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		// left arrow is pressed: move our ship left 5 pixels ( this is -5 pixels to go left)
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		yRotation = -90;
		this->sprite->setRotation(degrees(-90));
		this->move({ -DISTANCE, 0 });
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		// right arrow is pressed: move our ship right 5 pixels
		yRotation = 90;
		this->move({ DISTANCE, 0 });
		this->setRotation(degrees(90));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)) {
		xRotation = 1;
		this->move({ 0.0, -DISTANCE });
		this->setRotation(degrees(0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)) {
		xRotation = -1;
		this->move({ 0.0, DISTANCE });
		this->setRotation(degrees(180));
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		this->shootMissile();
	}

	if (xRotation != 0) {
		switch (yRotation) {
		case -90:
			direction = -45;
			if (xRotation < 0)
				direction = -135;
			break;
		case 90:
			direction = 45;
			if (xRotation < 0)
				direction = 135;
			break;
		default:
			switch (xRotation)
			{
			case(-1):
				direction = 180;
				break;
			case(1):
				direction = 0;
				break;
			}
		}
	}
	else {
		if (yRotation != 0)
			direction = yRotation;
	}
	this->setRotation(degrees(direction));
	updateMissiles();
}
