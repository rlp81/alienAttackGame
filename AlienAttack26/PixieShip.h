#pragma once
#include "gameHeader.h"

class ShipPixie : public Pixie {
private:
	friend class MissilePixie;
	friend class PlayerPixie;
	friend class EnemyPixie;
	double health;
	double damage;
	int activeMissileCount;
	int lastMissileFrame;
	int ammo;
	float direction;
	vector<int> missiles;
public:
	ShipPixie() = delete;
	virtual ~ShipPixie() = default;
	ShipPixie(int type, const std::string& textureFile);
	void shootMissile();
	bool damagePixie(double amount);
	void updateMissiles();
	static shared_ptr<ShipPixie> create(int type, const std::string& textureFile);
};