#include "gameHeader.h"

void ShipPixie::updateMissiles() {

	for (int id : missiles) {
		shared_ptr<MissilePixie> missile = MissilePixie::getMissileByID(id);
		if (missile)
		{
			bool off = missile->isOffScreen();
			if (off) {
				missile->remove();
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

void ShipPixie::shootMissile() {
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

ShipPixie::ShipPixie(int type, const std::string& textureFile) : Pixie(type, textureFile) {
	activeMissileCount = 0;
	lastMissileFrame = -1;
}

bool ShipPixie::damagePixie(double amount) {
	health -= amount;
	if (health <= 0) {
		Pixie::removePixieByID(this->getPixieID());
		return true;
	}
	return false;
}

shared_ptr<ShipPixie> ShipPixie::create(int type, const std::string& textureFile) {
	auto pixie = make_shared<ShipPixie>(type, textureFile);
	pixies.push_back(pixie);
	playerID = pixie->getPixieID();
	return pixie;
}