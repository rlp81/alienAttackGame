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
Swarm::Swarm(int controllerID, vector<int> &members) {
	this->controllerID = controllerID; // Set the controller to the specified controller
	this->members = members; // Add the Swarm's members to the swarm
	setupSwarm(); // Finish setting up the swarm
}

shared_ptr<Swarm> Swarm::create(int controllerID, vector<int>& members) {
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
	for (int memberId : members) { // Iterate through the active swarm members
		shared_ptr<EnemyPixie> member = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(memberId)); // Get the member by their Pixie ID
		if (memberId != controllerID) { // If the member is not the controller
			if (member == nullptr) { continue; } // Check if the member exists
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
int Swarm::findNewLeader(int lastLeader) {
	vector<int>::iterator it = std::find(members.begin(), members.end(), lastLeader) + 1; // Get the next member inline of the controller
	if (it != members.end()) { // Check if the member exists
		int index = std::distance(members.begin(), it); // get the index of the new leader
		shared_ptr<EnemyPixie> newLeader = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(members[index])); // get the Pixie of the new leader
		if (newLeader && newLeader != nullptr) { // Check if the new leader exists
			return members[index]; // return ID of the new leader
		}
		else {
			return findNewLeader(members[index]); // If the new leader does not exist, find the next in line
		}
	}
	else {
		return -1; // Return -1 if no new leader could be found

	}
}

/*
* updateSwarm()
* Params: None
* Returns: None
* Desc: Updates the Swarm
*/
void Swarm::updateSwarm() {
	for (int en : members) { // Iterate through the members of the swarm
		shared_ptr<EnemyPixie> enemy = dynamic_pointer_cast<EnemyPixie>(Pixie::getPixieByID(en)); // Get the Pixie of the swarm member
		if (enemy) { // Check if the member exists
			enemy->update(); // Update the member
		}
		else { // If the member doesn't exist
			if (this->controllerID == en) { // Check if the member is the controller
				controllerID = findNewLeader(en); // Find a new controller
				setupSwarm(); // Setup the new swarm configuration
			}
			EnemyPixie::enemies.erase(std::remove(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(), en), EnemyPixie::enemies.end()); // Erase the old leader from the active enemies vector
			members.erase(std::remove(members.begin(), members.end(), en), members.end()); // remove the old leader from the swarm members vector
		}

	}
}

void Swarm::updateAllSwarms() {
	for (shared_ptr<Swarm> swarm : swarms) { // Iterate through the existing swarms
		swarm->updateSwarm(); // Update each swarm
	}
}

void Swarm::removeEnemy(int enemyID) {
	members.erase(std::remove(members.begin(), members.end(), enemyID), members.end()); // Remove the enemy from the swarm members vector
	EnemyPixie::enemies.erase(std::remove(EnemyPixie::enemies.begin(), EnemyPixie::enemies.end(), enemyID), EnemyPixie::enemies.end()); // Remove the enemy from the active enemies vector
}

int Swarm::getTotalEnemyCount() {
	int total = 0; // Initialize the total swarm count to 0
	for (shared_ptr<Swarm> swarm : swarms) { // Iterate through the existing swarms
		if (swarm) { // Check if the swarm exists
			for (int member : swarm->members) { // Iterate through the members of the swarm
				if (Pixie::getPixieByID(member)) { // Check if the member exists
					total++; // Increment the total count
				}
			}
		}
	}
	return total; // Return the total count
}