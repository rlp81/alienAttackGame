#pragma once
#include "gameHeader.h" 

class MissilePixie : public Pixie {
private:
	PlayerPixie* owner;
	float direction;
public:
	MissilePixie(PlayerPixie* owner);
	virtual ~MissilePixie() = default;
	void update();
	bool checkCollision();
	static shared_ptr<MissilePixie> getMissileByID(int id);
	void remove();
	static shared_ptr<MissilePixie> create(PlayerPixie* owner);
};