#pragma once
#include "gameHeader.h" 

class EnemyPixie : public Pixie {
private:
	double health;
	double damage;
	string faction;
	int enemyType;
	int movePattern;
	shared_ptr<Pixie> target;
	int followPadding;
public:
	EnemyPixie();
	static shared_ptr<EnemyPixie> create();
	static shared_ptr<EnemyPixie> create(int targetID);
	shared_ptr<Pixie> getTarget() const { return target; }
	void setPattern(int pattern) { movePattern = pattern; }
	void orbit(float radius);
	void orbit(float radius, shared_ptr<Pixie> target);
	void followTarget();
	void followTarget(shared_ptr<Pixie> target);
	void update();
};