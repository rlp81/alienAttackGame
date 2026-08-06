#include "gameHeader.h"
/*
* PixieEnemy.cpp
* Description: function C++ file for the PixieEnemy Class
* Author: Cole
*/
int EnemyPixie::enemyMissileCount = 0; // Initialize the active enemy missile count to 0
vector<weak_ptr<EnemyPixie>> EnemyPixie::enemies; // Initialize the active enemies in the game
// Constructors

/*
* EnemyPixie()
* Params: None
* Returns: None
* Desc: Creates an EnemyPixie
*/
EnemyPixie::EnemyPixie() : ShipPixie(PIXIE_TYPE_ENEMY, DEFAULT_ENEMY_TEXTURE) {
	scoreWorth = 100;
	health = ENEMY_PIXIE_HEALTH; // Set the health to the default Pixie Health
	damage = 1; // Set the default damage to 3.4
	faction = "Glorps"; // Set the faction to Glorps
	enemyType = 0; // Set the enemy type to 0
	orbitDirection = 1; // Set the default orbit direction to 1
	movePattern = 0; // Set the move pattern to 0
	followPadding = 50; // Set the default follow padding to 50
	target = nullptr; // Set the target to the nullptr
	targetType = 0; // Set the target type to 0
	speed = DEFAULT_PIXIE_SPEED * 0.75f; // Set the speed to 75% of the default pixie speed
	//activeMissileCount = 0; // Set the active missile count to 0
	canFireMissile = true; // Set the enemy to be able to fire
	randomPoint = Vector2f(0, 0); // Set the default random point to (0,0)
	swarm = nullptr; // Set the swarm to nullptr, the Enemy is not in a swarm by default
	lastRandomMoveFrame = -RANDOM_MOVE_COOLDOWN; // Set the last random move frame to 0
}

/*
* create()
* Params: None
* Returns: shared_ptr<EnemyPixie>
* Desc: Creates an EnemyPixie as a shared pointer and adds it to the active enemy vector and pixies vector
*/
shared_ptr<EnemyPixie> EnemyPixie::create() {
	auto enemy = make_shared<EnemyPixie>(); // Create an EnemyPixie as a shared pointer
	enemies.push_back(enemy); // Place the EnemyPixie's ID into the active enemy list
	pixies[enemy->pixieID] = enemy; // Place the EnemyPixie in the active Pixie vector
	return enemy; // Return the shared pointer EnenmyPixie
}

/*
* create(int targetID)
* Params: int targetID - The Pixie for the EnemyPixie to target
* Returns: shared_ptr<EnemyPixie>
* Desc: Creates an EnemyPixie and sets their target as a shared pointer and adds it to the active enemy vector and pixies vector
*/
shared_ptr<EnemyPixie> EnemyPixie::create(int targetID) {
	auto enemy = make_shared<EnemyPixie>(); // Create an EnemyPixie as a shared pointer
	enemies.push_back(enemy); // Place the EnemyPixie's ID into the active enemy list
	enemy->target = Pixie::getPixieByID(targetID); // Set the target pixie to the selected Pixie's ID
	pixies[enemy->pixieID] = enemy; // Place the EnemyPixie in the active Pixie vector
	return enemy; // Return the shared pointer EnenmyPixie
}

void EnemyPixie::moveRandomly() {
	bool shouldMoveRandomly = false;
	// Check if the random point is the default (0,0) or if the Enemy has reached the random point
	if ((randomPoint.x == 0 && randomPoint.y == 0) || ((this->getPosition() - randomPoint).length() <= 3)) {
		if (lastRandomMoveFrame + RANDOM_MOVE_COOLDOWN < currentFrame) {
			lastRandomMoveFrame = currentFrame;
			int XRandom = (rand() % ((WINDOW_WIDTH + 1) - 100)) + 100;
			int YRandom = (rand() % ((WINDOW_HEIGHT + 1) - 100)) + 100;
			Vector2f randomPoint = Vector2f(XRandom, YRandom); // Create a random point to move towards
			this->randomPoint = randomPoint; // Set the random point variable to the created random point
			cout << "New random point: " << XRandom << ", " << YRandom << endl; // Print the new random point to the console for testing
		}
		else {
			shouldMoveRandomly = false; // If the Enemy has reached the random point or the cooldown has not passed, do not move randomly
		}
	}
	else {
		shouldMoveRandomly = true; // If the Enemy has not reached the random point, move randomly
	}
	if (shouldMoveRandomly) {
		Vector2f direction = randomPoint - this->getPosition(); // Get the direction from the Enemy to the random point
		float length = direction.length();
		if (length != 0) { // If the length isnt 0
			direction /= length; // divide the alient direction by the length to get a unit vector
		}
		this->move(direction * speed); // Move the Enemy in the unit direction with the Pixie's speed
	}
}

/*
* followTarget()
* Params: None
* Returns: None
* Desc: Follows a target or leader based on the targeting type and movement settings
*/
void EnemyPixie::followTarget() {

	Vector2f alienDirection; // Variable for what direction the enemy is pointing
	shared_ptr<Pixie> lead = Pixie::getPixieByID(leader); // the Swarm's leader
	if (targetType == 2 && lead) { // Check if the Enemy is targetting the leader
		alienDirection = this->getPosition() - lead->getPosition(); // Get the direction from the Enemy to leader
	}
	else if (targetType == 1 && target){ // Check if the Enemy is targetting the target
		alienDirection = this->getPosition() - target->getPosition(); // Get the direction from the Enemy to target
	}
	else {
		return; // If the target type doesnt exist return
	}
	float length = alienDirection.length(); // the length of direction

	if (length != 0) { // If the length isnt 0
		alienDirection /= length; // divide the alient direction by the length to get a unit vector
	}
	if (length < followPadding + (this->sprite->getGlobalBounds().size.x / 2) || length < followPadding + (this->sprite->getGlobalBounds().size.y / 2)) { // Check if the Enemy is inside the follow padding
		return this->orbit(); // Orbit the target/leader
	}

	this->move(alienDirection * -this->speed); // Move the Pixie in the unit direction with the Pixie's speed
}

/*
* followTarget()
* Params: shared_ptr<Pixie> target - The target to be followed
* Returns: None
* Desc: Follows a specified target on based on the movement settings
*/
void EnemyPixie::followTarget(shared_ptr<Pixie> target) {
	this->target = target; // Set the target to the specified target
	targetType = 1; // Set the target to 1 so it follows the target
	followTarget(); // Call the original function
}

/*
* orbit()
* Params: None
* Returns: None
* Desc: Orbit a target or leader
*/
void EnemyPixie::orbit() {
	float rads; // Create the variable to hold the radian angle
	shared_ptr<Pixie> lead = Pixie::getPixieByID(leader); // Leader of the Swarm
	if (targetType == 1 && target) { // Check if Enemy is targetting the target
		rads = target->getDirectionTo(*this); // Get the direction to the target
	}
	else if (targetType == 2 && lead) { // Check if Enemy is targetting the leader
		rads = lead->getDirectionTo(*this); // Get the direction to the leader
	}
	float degs = rads * 180 / 3.14159265f; // Convert the radians to degrees
	rads = degrees(degs + (90*orbitDirection)).asRadians(); // Add a 90 degree offset to the direction to move
	float offsetX = cos(rads) * speed; // X axis offset
	float offsetY = sin(rads) * speed; // Y axis offset
	this->move(offsetX, offsetY); // Move the Enemy in the direction at the specific speed
}

/*
* shootMissile()
* Params: None
* Returns: None
* Desc: Shoots a missile from the Enemy
*/
void EnemyPixie::shootMissile() {
	if (!canFireMissile) { return; } // Check if the Enemy can fire a missile
	if (!(currentFrame >= DEFAULT_FRAMES_TILL_NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) { // Check if the Enemy Pixie can fire a Missile via time from last missile launch
		return; // Quit the function
	}
	if (enemyMissileCount > MAX_ACTIVE_MISSILES) { // Check if there are too many ative missiles
		//std::cout << "Maximum active missiles reached!" << std::endl; // Return and error
		return; // Quit the function
	}
	if (ammo > 0) { // Check if the Enemy has any ammo
		vector<int> ignoreList = { this->pixieID }; // The list of Pixies to ignore in the RayCast
		RayCast ray = RayCast(this->getPosition(), this->getRotation(), ignoreList); // Create a raycast to check if the Enemy has a line of sight to the target
		if (ray.isHit() && ray.getResultID() == target->getPixieID()) { // Check if the there was a result from the raycast and if the result was the target
			cout << "Shooting missile! Ammo left: " << ammo << endl; // Print that the Enemy is shooting a missile
			lastMissileFrame = currentFrame; // Set the last frame to fire a missile to the current frame
			shared_ptr<MissilePixie> missile = MissilePixie::create(this); // Create a shared pointer of a missile
			if (missile) { // Check if the missile was created successfully
				ammo--; // Add one to the active enemy missile count
			}
		}
	}
	else {
		std::cout << "Out of ammo!" << std::endl; // Declare the Enemy Pixie is out of ammo
	}
}

/*
* update()
* Params: None
* Returns: None
* Desc: Update the EnemyPixie
*/
void EnemyPixie::update() {
	switch (movePattern) // Switch the current move pattern
	{
		case 0: // If 0, follow target
			followTarget();
			break;
		case 2: // If 2, move randomly
			moveRandomly();
			break;
		default: // otherwise follow target
			followTarget(); 
			break;
	}
	if (target) { // Check if the target exists
		float rads = target->getDirectionTo(*this); // Get the direction to the target
		float degs = rads * 180 / 3.14159265f - 90; // Correctly orientate the Enemy
		this->setRotation(degrees(degs)); // Set the rotation to previous direciton
		shootMissile(); // Try and shoot a missile

	}
	else {
		this->setRotation(degrees(0)); // If the target doesn't exist set the rotation to 0
	}
}

/*
* damagePixie(double amount)
* Params: double amount - Amount of health to be redated from the ShipPixie
* Returns: bool
* Desc: Damages the ShipPixie and return if it is dead
*/
bool EnemyPixie::damagePixie(double amount) {
	health -= amount; // Removes an amount from the Pixie's health
	if (health <= 0) { // Check if the health is below or equal to 0

		Pixie::removePixieByID(this->getPixieID()); // Remove the Pixie if it is dead
		
		return true; // return true for dead
	}
	return false; // return false for alive
}
