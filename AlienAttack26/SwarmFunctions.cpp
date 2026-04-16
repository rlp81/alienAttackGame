#include "gameHeader.h"
/*
* SwarmFunctions.cpp
* Description: function C++ file for the Swarm Class
* Author: Cole Lehl
*/

vector<shared_ptr<Swarm>> Swarm::swarms; // Initialize the static vector of swarms

/*
* Swarm(int controllerID, vector<int> &members)
* Params: int controllerID - The Pixie ID for the controlling enemy, vector<int> &members - The vector of the enemys to be added to the swarm
* Returns: None
* Desc: Creates an Swarm
*/
Swarm::Swarm(int controllerID, vector<weak_ptr<EnemyPixie>> &members) {
	this->controllerID = controllerID; // Set the controller to the specified controller
	this->members = members; // Add the Swarm's members to the swarm
	setupSwarm(); // Finish setting up the swarm
}

shared_ptr<Swarm> Swarm::create(int controllerID, vector<weak_ptr<EnemyPixie>>& members) {
	auto swarm = make_shared<Swarm>(controllerID, members);
	swarms.push_back(swarm);
	return swarm;
}

/*
* setupSwarm()
* Params: None
* Returns: None
* Desc: Set up the swarm members to follow and orbit the controller
Changes the swarm's leader based on the next enemy after the controller in the swarm members vector
*/
void Swarm::setupSwarm() {
	//shared_ptr<Pixie> controller = Pixie::getPixieByID(controllerID);
	int padding = DEFAULT_PADDING; // The default padding that the swarm members will orbit the leader by
	for (auto memberP : members) { // Iterate through the active swarm members
		shared_ptr<EnemyPixie> member = memberP.lock();
		if (member == nullptr || member == NULL) { continue; } // Check if the member exists
		if (member->pixieID != controllerID) { // If the member is not the controller
			member->leader = controllerID; // Set their leader to the controller
			member->targetType = 2; // Set their targeting type
			member->followPadding = padding; // Set their padding
			padding += PADDING_INCREMENT; // Iterate the padding by a set amount
		}
		else {
			member->speed = DEFAULT_PIXIE_SPEED - 1.0f; // Set the controller's speed to be slower than the other members
			member->movePattern = 2; // Set the controller's movement pattern to 2, which is a custom pattern for the controller that is based on the movement of the swarm members
		}
	}
}
/*
* findNewLeader()
* Params: int lastLeader - The last leader's ID
* Returns: int
* Desc: Changes the swarm's leader based on the next enemy after the controller in the swarm members vector
*/
int Swarm::findNewLeader(int lastLeaderID) {
	auto it = std::find_if(members.begin(), members.end(),
		[lastLeaderID](const std::weak_ptr<EnemyPixie>& wp) {
			auto sp = wp.lock();
			return sp && sp->getPixieID() == lastLeaderID;
		});
	if (it != members.end()) {
		++it;
		while (it != members.end()) {
			auto sp = it->lock();
			if (sp) {
				return sp->getPixieID();
			}
			++it;
		}
	}
	return -1;
}

/*
* updateSwarm()
* Params: None
* Returns: None
* Desc: Updates the Swarm
*/
void Swarm::updateSwarm() {
	for (auto en : members) { // Iterate through the members of the swarm
		shared_ptr<EnemyPixie> enemy = en.lock(); // Get the Pixie of the swarm member
		if (enemy == nullptr || enemy == NULL) { continue; } // Check if the member exists
		if (enemy) { // Check if the member exists
			enemy->update(); // Update the member
		}
		else { // If the member doesn't exist
			if (this->controllerID == enemy->pixieID) { // Check if the member is the controller
				controllerID = findNewLeader(enemy->pixieID); // Find a new controller
				setupSwarm(); // Setup the new swarm configuration
			}
			EnemyPixie::enemies.erase(
				std::remove_if(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(),
					[](const std::weak_ptr<EnemyPixie>& wp) {
						return wp.expired(); // True if the shared_ptr is dead
					}),
				EnemyPixie::enemies.end()
			);;
			members.erase(
				std::remove_if(members.begin(), members.end(),
					[](const std::weak_ptr<EnemyPixie>& wp) {
						return wp.expired(); // True if the shared_ptr is dead
					}),
				members.end()
			);
		}

	}
}

void Swarm::updateAllSwarms() {
	for (shared_ptr<Swarm> swarm : swarms) { // Iterate through the existing swarms
		swarm->updateSwarm(); // Update each swarm
	}
}

void Swarm::removeEnemy(int enemyID) {
	EnemyPixie::enemies.erase(
		std::remove_if(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(),
			[enemyID](weak_ptr<EnemyPixie>& wp) {
				if (shared_ptr<EnemyPixie> sp = wp.lock())
					return sp->pixieID == enemyID; // True if IDs match
			}),
		EnemyPixie::enemies.end()
	);

	members.erase(
		std::remove_if(members.begin(), members.end(),
			[enemyID](weak_ptr<EnemyPixie>& wp) {
				if (shared_ptr<EnemyPixie> sp = wp.lock())
					return sp->pixieID == enemyID; // True if IDs match
			}),
		members.end()
	);
	
}

int Swarm::getTotalEnemyCount() {
	int total = 0; // Initialize the total swarm count to 0
	for (shared_ptr<Swarm> swarm : swarms) { // Iterate through the existing swarms
		if (swarm) { // Check if the swarm exists
			for (auto member : swarm->members) { // Iterate through the members of the swarm
				if (member.lock()) { // Check if the member exists
					total++; // Increment the total count
				}
			}
		}
	}
	return total; // Return the total count
}