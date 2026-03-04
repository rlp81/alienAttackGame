#include "gameHeader.h"

Swarm::Swarm(int controllerID, vector<int> &members) {
	this->controllerID = controllerID;
	this->members = members;
	shared_ptr<EnemyPixie> controller = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(controllerID));
	int padding = DEFAULT_PADDING;
	for (int memberId : members) {
		if (memberId != controllerID) {
			shared_ptr<EnemyPixie> member = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(memberId));
			member->leader = controller;
			member->targetType = 2;
			member->followPadding = padding;
			padding += PADDING_INCREMENT;
		}
	}
}

void Swarm::updateSwarm() {
	for (int en : members) {
		shared_ptr<EnemyPixie> enemy = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(en));
		if (enemy) {
			enemy->update();
		}
		else {
			EnemyPixie::enemies.erase(std::remove(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(), en), EnemyPixie::enemies.end());
		}

	}
}