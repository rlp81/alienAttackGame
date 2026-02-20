#include "gameHeader.h"

PlayerPixie::PlayerPixie() : Pixie(1, DEFAULT_SHIP_TEXTURE) {
	setSpeed(DEFAULT_PIXIE_SPEED);
	setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	ammo = DEFAULT_PLAYER_AMMO;
	health = DEFAULT_PIXIE_HEALTH;
	activeMissileCount = 0;
	lastMissileFrame = -1;
}

shared_ptr<PlayerPixie> PlayerPixie::create() {
	auto player = make_shared<PlayerPixie>();
	pixies.push_back(player);
	return player;
}

void PlayerPixie::shootMissile() {
	if (!(currentFrame >= DEFAULT_FRAMES_TILL__NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) {
		return;
	}
	if (activeMissileCount >= MAX_ACTIVE_MISSILES) {
		std::cout << "Maximum active missiles reached!" << std::endl;
		return;
	}
	if (ammo > 0) {
		cout << "Shooting missile! Ammo left: " << ammo << endl;
		lastMissileFrame = currentFrame;
		MissilePixie::create(this);
		activeMissileCount++;
		ammo--;
	}
	else {
		std::cout << "Out of ammo!" << std::endl;
	}
}

bool MissilePixie::checkCollision() {
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
	int angle = 0;

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
			angle = -45;
			if (xRotation < 0)
				angle = -135;
			break;
		case 90:
			angle = 45;
			if (xRotation < 0)
				angle = 135;
			break;
		default:
			switch (xRotation)
			{
			case(-1):
				angle = 180;
				break;
			default:
				angle = 0;
				break;
			}
		}
	}
	else {
		angle = yRotation;
	}
	this->setRotation(degrees(angle));
	this->direction = angle;
	updateMissiles();
}

void PlayerPixie::updateMissiles() {

	for (int id : missiles) {
		shared_ptr<MissilePixie> missile = MissilePixie::getMissileByID(id);
		if (missile)
		{
			bool off = missile->isOffScreen();
			if (off) {
				size_t index = missile->getPixieID();
				auto* targetRawPtr = &missile;
				missiles.erase(std::remove(missiles.begin(), missiles.end(), id), missiles.end());
				/*missiles.erase(
					std::remove_if(missiles.begin(), missiles.end(),
						[targetRawPtr](const std::shared_ptr<MissilePixie>& p) {
							return p.get() == targetRawPtr;
						}),
					missiles.end()
				);*/
				auto it = std::find(pixies.begin(), pixies.end(), missile);
				if (it != pixies.end()) {
					pixies.erase(it);
				}
				//pixies[index].reset();
				this->activeMissileCount--;
			}
			else {
				missile->update();
			}
		}
		else {
			missiles.erase(std::remove(missiles.begin(), missiles.end(), id), missiles.end());
		}
	}
}