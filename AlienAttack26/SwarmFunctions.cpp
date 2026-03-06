#include "gameHeader.h"

Swarm::Swarm(int controllerID, vector<int> &members) {
	this->controllerID = controllerID;
	this->members = members;
	changeLeader();
}

void Swarm::changeLeader() {
	shared_ptr<Pixie> controller = Pixie::getPixieByID(controllerID);
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

int Swarm::findNewLeader(int lastLeader) {
	vector<int>::iterator it = std::find(members.begin(), members.end(), lastLeader) + 1;
	if (it != members.end()) {
		int index = std::distance(members.begin(), it);
		shared_ptr<EnemyPixie> newLeader = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(members[index]));
		if (newLeader && newLeader != nullptr) {
			return members[index];
		}
		else {
			return findNewLeader(members[index]);
		}
	}
	else {
		return -1;

	}
}

void Swarm::updateSwarm() {
	for (int en : members) {
		shared_ptr<EnemyPixie> enemy = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(en));
		if (enemy) {
			enemy->update();
		}
		else {
			if (this->controllerID == en) {
				controllerID = findNewLeader(en);
				changeLeader();
			}
			EnemyPixie::enemies.erase(std::remove(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(), en), EnemyPixie::enemies.end());
			members.erase(std::remove(members.begin(), members.end(), en), members.end());
		}

	}
}