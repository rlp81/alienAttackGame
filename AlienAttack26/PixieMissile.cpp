#include "gameHeader.h"

void::MissilePixie::update() {
	if (owner) {
		float rads = this->getRotation().asRadians();
		double x = cos(rads);
		double y = sin(rads);
		if (abs(x) == 1) {
			this->move(Vector2f(y, x) * -MISSILE_SPEED);
		}
		else if (abs(x) != 1 && abs(y) != 1) {
			if (to_string(x * -1) == to_string(y)) {
				this->move(Vector2f(x, y * -1) * -MISSILE_SPEED);
			}
			else if (to_string(x) == to_string(y)) {
				this->move(Vector2f(x, y * -1) * MISSILE_SPEED);
			}
		}
		else {
			this->move(Vector2f(y, x) * MISSILE_SPEED);
		}
	}
	else {
		std::cerr << "Owner not set for MissilePixie!" << std::endl;
	}
}

void MissilePixie::remove() {
	/*deletedPixies.push_back(this->getPixieID());
	owner->missiles.erase(std::remove(owner->missiles.begin(), owner->missiles.end(), this), owner->missiles.end());
	pixies.erase(std::remove(pixies.begin(), pixies.end(), this), pixies.end());
	owner->activeMissileCount--;*/
}

MissilePixie::MissilePixie(PlayerPixie* owner) : Pixie(2, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED);
	this->owner = owner;
	this->setPosition(owner->getPosition());
	direction = owner->direction;
	this->setRotation(degrees(direction));
	cout << "Fired\n";
}



shared_ptr<MissilePixie> MissilePixie::getMissileByID(int id) {
	for (const auto& pixie : Pixie::pixies) {
		if (pixie->getPixieID() == id) {
			return std::dynamic_pointer_cast<MissilePixie>(pixie);
		}
	}
	return nullptr;
}

shared_ptr<MissilePixie> MissilePixie::create(PlayerPixie* owner) {
	auto missile = make_shared<MissilePixie>(owner);
	pixies.push_back(missile);
	owner->missiles.push_back(missile->getPixieID());
	return missile;
}