#pragma once
#include "gameHeader.h" 

class MissilePixie : public Pixie {
private:
	ShipPixie* owner;
	float direction;
	float damage;
public:
	MissilePixie(ShipPixie* owner);
	virtual ~MissilePixie() = default;
	void update();
	bool checkCollision();
	static shared_ptr<MissilePixie> getMissileByID(int id);
	void remove();
	static shared_ptr<MissilePixie> create(ShipPixie* owner);
	void checkForCollisions();
};