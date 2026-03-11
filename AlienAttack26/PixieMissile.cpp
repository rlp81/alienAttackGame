#include "gameHeader.h"

void::MissilePixie::update() {
	/*float rads = this->getRotation().asRadians();
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
	}*/

	float rads = this->getRotation().asRadians();
	float degs = rads * 180 / 3.14159265f;
	rads = degrees(degs+90).asRadians();
	float offsetX = std::cos(rads) * -speed;
	float offsetY = std::sin(rads) * -speed;
	this->move(offsetX, offsetY);
}

void MissilePixie::remove() {
	int id = this->getPixieID();
	owner->missiles.erase(std::remove(owner->missiles.begin(), owner->missiles.end(), id), owner->missiles.end());
	Pixie::removePixieByID(id);
	owner->activeMissileCount--;
}

MissilePixie::MissilePixie(ShipPixie* owner) : Pixie(PIXIE_TYPE_MISSILE, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED);
	this->owner = owner;
	this->setPosition(owner->getPosition());
	this->setRotation(owner->getRotation());
	this->damage = owner->damage;
}

MissilePixie::MissilePixie(ShipPixie* owner, float angle) : Pixie(2, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED);
	this->owner = owner;
	this->setPosition(owner->getPosition());
	direction = angle;
	this->setRotation(degrees(direction));
	this->damage = owner->damage;
}

shared_ptr<MissilePixie> MissilePixie::create(ShipPixie* owner, float angle) {
	auto missile = make_shared<MissilePixie>(owner, angle);
	pixies.push_back(missile);
	owner->missiles.push_back(missile->getPixieID());
	return missile;
}

shared_ptr<MissilePixie> MissilePixie::getMissileByID(int id) {
	for (const auto& pixie : Pixie::pixies) {
		if (pixie->getPixieID() == id) {
			return std::dynamic_pointer_cast<MissilePixie>(pixie);
		}
	}
	return nullptr;
}

shared_ptr<MissilePixie> MissilePixie::create(ShipPixie* owner) {
	auto missile = make_shared<MissilePixie>(owner);
	pixies.push_back(missile);
	owner->missiles.push_back(missile->getPixieID());
	return missile;
}

void MissilePixie::checkForCollisions() {
	{
		if (Pixie::getPixieByID(owner->getPixieID()) == nullptr) {
			return;
		}
		for (const auto& pixie : Pixie::pixies) {
			if (pixie == nullptr || pixie->sprite == nullptr || pixie == NULL || pixie->sprite == NULL) {
				continue;
			}
			int pixieType = pixie->getPixieType();
			if (this->getPixieID() != pixie->getPixieID() && pixie->getPixieID() != owner->getPixieID() && pixie->pixieType != 0) {
				if (this->isCollidingWith(*pixie)) {
					shared_ptr<ExplosionPixie> exp = ExplosionPixie::create(3, DEFAULT_EXPLOSION_TEXTURE, this->sprite->getPosition());
					if (pixieType == 3) {
						/*shared_ptr<EnemyPixie> enemy = std::dynamic_pointer_cast<EnemyPixie>(pixie);
						if (enemy) {
							if (bool died = enemy->damagePixie(damage)) {
								if (this->owner->getPixieType() == 1) {
									playerScore += 100;
								}
							}
						}*/
					}
					this->remove();
					break;
				}
			}
		}
	}
}