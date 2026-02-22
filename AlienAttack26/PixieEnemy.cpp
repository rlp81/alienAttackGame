#include "gameHeader.h"

EnemyPixie::EnemyPixie() : ShipPixie(3, DEFAULT_ENEMY_TEXTURE) {
	health = DEFAULT_PIXIE_HEALTH;
	damage = 3.4;
	faction = "Glorps";
	enemyType = 0;
	movePattern = 0;
	followPadding = 50;
	target = nullptr;
	speed = DEFAULT_PIXIE_SPEED * 0.75f;
	activeMissileCount = 0;
}

shared_ptr<EnemyPixie> EnemyPixie::create() {
	auto enemy = make_shared<EnemyPixie>();
	pixies.push_back(enemy);
	return enemy;
}

shared_ptr<EnemyPixie> EnemyPixie::create(int targetID) {
	auto enemy = make_shared<EnemyPixie>();
	enemy->target = Pixie::getPixieByID(targetID);
	enemy->setPosition(100, 100);
	pixies.push_back(enemy);
	return enemy;
}

void EnemyPixie::followTarget() {
	Vector2f alienDirection = this->getPosition() - target->getPosition();
	float length = alienDirection.length();

	if (length != 0) {
		alienDirection /= length;
	}
	if (length < followPadding + (this->sprite->getGlobalBounds().size.x / 2) || length < followPadding + (this->sprite->getGlobalBounds().size.y / 2)) {
		return this->orbit(followPadding);
	}

	this->move(alienDirection * -this->speed);
}

void EnemyPixie::followTarget(shared_ptr<Pixie> target) {
	this->target = target;
	followTarget();
}

void EnemyPixie::orbit(float radius) {
	if (target) {
		float rads = target->getDirectionTo(*this);
		float degs = rads * 180 / 3.14159265f;
		rads = degrees(degs + 90).asRadians();
		float offsetX = std::cos(rads) * speed;
		float offsetY = std::sin(rads) * speed;
		this->move(offsetX, offsetY);
	}
}

void EnemyPixie::shootMissile() {
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
		shared_ptr<MissilePixie> missile = MissilePixie::create(this);
		
		activeMissileCount++;
		ammo--;
	}
	else {
		std::cout << "Out of ammo!" << std::endl;
	}
}

void EnemyPixie::update() {
	switch (movePattern)
	{
		case 0:
			followTarget();
			break;
		default:
			followTarget();
			break;
	}
	if (target) {
		float rads = target->getDirectionTo(*this);
		float degs = rads * 180 / 3.14159265f - 90;
		this->setRotation(degrees(degs));
		shootMissile();
		updateMissiles();
	}
	else {
		this->setRotation(degrees(0));
	}
}