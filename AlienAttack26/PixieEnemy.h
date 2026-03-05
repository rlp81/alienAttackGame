#pragma once
#include "gameHeader.h" 

class EnemyPixie : public ShipPixie {
private:
	friend class Swarm;
	string faction;
	int enemyType;
	int movePattern;
	int targetType;
	int orbitDirection;
	shared_ptr<Pixie> target;
	shared_ptr<Pixie> leader;
	int followPadding;
	bool canFireMissile;
public:
	static vector<int> enemies;
	EnemyPixie();
	static shared_ptr<EnemyPixie> create();
	static shared_ptr<EnemyPixie> create(int targetID);
	void setFollowPadding(int padding) { followPadding = padding; }
	int getFollowPadding() { return followPadding; }
	shared_ptr<Pixie> getTarget() const { return target; }
	void setPattern(int pattern) { movePattern = pattern; }
	void orbit();
	void orbit(float radius, shared_ptr<Pixie> target);
	void followTarget();
	void shootMissile();
	void changeOrbitDirection() { orbitDirection *= -1; }
	void followTarget(shared_ptr<Pixie> target);
	void update();
};
