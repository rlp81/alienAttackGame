#pragma once
#include "gameHeader.h" 

class PlayerPixie : public ShipPixie {
private:
	friend class MissilePixie;
public:
	PlayerPixie();
	void update();
	static shared_ptr<PlayerPixie> create();
};