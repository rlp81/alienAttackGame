#include "gameHeader.h"
vector<int> EnemyPixie::enemies;

EnemyPixie::EnemyPixie() : ShipPixie(3, DEFAULT_ENEMY_TEXTURE) {
	health = DEFAULT_PIXIE_HEALTH;
	damage = 3.4;
	faction = "Glorps";
	enemyType = 0;
	orbitDirection = 1;
	movePattern = 0;
	followPadding = 50;
	target = nullptr;
	targetType = 0;
	speed = DEFAULT_PIXIE_SPEED * 0.75f;
	activeMissileCount = 0;
	canFireMissile = true;
}

shared_ptr<EnemyPixie> EnemyPixie::create() {
	auto enemy = make_shared<EnemyPixie>();
	enemies.push_back(enemy->pixieID);
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

	Vector2f alienDirection;
	if (targetType == 2 && leader) {
		alienDirection = this->getPosition() - leader->getPosition();
	}
	else if (targetType == 1 && target){
		alienDirection = this->getPosition() - target->getPosition();
	}
	else {
		return;
	}
	float length = alienDirection.length();

	if (length != 0) {
		alienDirection /= length;
	}
	if (length < followPadding + (this->sprite->getGlobalBounds().size.x / 2) || length < followPadding + (this->sprite->getGlobalBounds().size.y / 2)) {
		return this->orbit();
	}

	this->move(alienDirection * -this->speed);
}

void EnemyPixie::followTarget(shared_ptr<Pixie> target) {
	this->target = target;
	targetType = 1;
	followTarget();
}

void EnemyPixie::orbit() {
	float rads;
	if (targetType == 1 && target) {
		rads = target->getDirectionTo(*this);
	}
	else if (targetType == 2 && leader) {
		rads = leader->getDirectionTo(*this);	
	}
	float degs = rads * 180 / 3.14159265f;
	rads = degrees(degs + (90*orbitDirection)).asRadians();
	float offsetX = std::cos(rads) * speed;
	float offsetY = std::sin(rads) * speed;
	this->move(offsetX, offsetY);
}

void EnemyPixie::shootMissile() {
	if (!canFireMissile) { return; }
	if (!(currentFrame >= DEFAULT_FRAMES_TILL__NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) {
		return;
	}
	if (activeMissileCount >= MAX_ACTIVE_MISSILES) {
		std::cout << "Maximum active missiles reached!" << std::endl;
		return;
	}
	if (ammo > 0) {
		vector<int> ignoreList = { this->pixieID };
		RayCast ray = RayCast(this->getPosition(), this->getRotation(), ignoreList);
		if (ray.isHit() && ray.getResultID() == target->getPixieID()) {
			cout << "Shooting missile! Ammo left: " << ammo << endl;
			lastMissileFrame = currentFrame;
			shared_ptr<MissilePixie> missile = MissilePixie::create(this);

			activeMissileCount++;
			ammo--;
		}
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