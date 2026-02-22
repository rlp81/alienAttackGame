#pragma once
#include "gameHeader.h" 

class MissilePixie : public Pixie {
private:
	ShipPixie* owner;
	float direction;
	float damage;
public:
	MissilePixie(ShipPixie* owner);
	MissilePixie(ShipPixie* owner, float angle);
	virtual ~MissilePixie() = default;
	void update();
	bool checkCollision();
	static shared_ptr<MissilePixie> getMissileByID(int id);
	void remove();
	static shared_ptr<MissilePixie> create(ShipPixie* owner);
	static shared_ptr<MissilePixie> create(ShipPixie* owner, float angle);
	void checkForCollisions();
};