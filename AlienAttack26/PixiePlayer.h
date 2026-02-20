#pragma once
#include "gameHeader.h" 

class PlayerPixie : public Pixie {
private:
	friend class MissilePixie;
	int ammo;
	int health;
	int activeMissileCount;
	float direction;
	int lastMissileFrame;
	//vector<MissilePixie*> missiles;
	vector<int> missiles;
public:
	PlayerPixie();
	void shootMissile();
	void update();
	void updateMissiles();
	static shared_ptr<PlayerPixie> create();
};