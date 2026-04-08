#include "gameHeader.h"
/*
* pixie.cpp
* Description: function C++ file for the Pixie Class and it's related static variables
* Author: Cole Lehl
*/

// Static Variable Initialization

int Pixie::nextPixieID = 0; // initialize the next Pixie ID to 0
int Pixie::pixieCount = 0; // initialize the Pixie count to 0
vector<std::shared_ptr <Pixie>> Pixie::pixies; // initialize the vector of pixies to be empty

// Constructors

/*
* Pixie(int type)
* Params: int type - the type of Pixie to create
* Desc: Creates a basic Pixie with no Texture but with a type
*/
Pixie::Pixie(int type) {
	pixieType = type; // Set the type
	pixieID = nextPixieID++; // iterate the next Pixie ID and set the Pixie's ID to the current next Pixie ID
	active = true; // Set the Pixie to be active
	sprite = nullptr; // set the sprite to nullptr to avoid uninitialized pointer issues
	texture = nullptr; // set the texture to nullptr to avoid uninitialized pointer issues
}

/*
* Pixie(int type, const string& textureFile)
* Params: int type - the type of Pixie to create; const string& textureFile - the file path to the texture to be used for the Pixie
* Desc: Creates a basic Pixie with both a texture and type
*/
Pixie::Pixie(int type, const string& textureFile) {
	pixieType = type; // Set the type
	texture = new sf::Texture(); // Create a Texture pointer for the Pixie
	if (!texture->loadFromFile(textureFile)) { // Try and load a the texture from the file, if not error to the console and exit the program
		std::cerr << "Failed to load texture from file: " << textureFile << std::endl;
		exit(EXIT_FAILURE);
	}
	sprite = new sf::Sprite(*texture); // Create a sprite pointer for the Pixie
	sprite->setOrigin(getSpriteCenter(*sprite)); // Set the origin of the sprite to the center of the sprite
	sprite->setScale({ DEFAULT_PIXIE_SCALE,DEFAULT_PIXIE_SCALE }); // Set the scale of the sprite to the default Pixie scale
	pixieID = nextPixieID++; // iterate the next Pixie ID and set the Pixie's ID to the current next Pixie ID
	active = true; // Set the Pixie to be active
}

/*
* Pixie(int type, const string& textureFile, bool useOriginalOrigin)
* Params: int type - the type of Pixie to create; const string& textureFile - the file path to the texture to be used for the Pixie; bool useOriginalOrigin - whether or not to use the original origin of the sprite (0,0)
* Desc: Creates a basic Pixie with both a texture and type
*/
Pixie::Pixie(int type, const std::string& textureFile, bool useOriginalOrigin) {
	pixieType = type; // Set the type
	texture = new sf::Texture(); // Create a Texture pointer for the Pixie
	if (!texture->loadFromFile(textureFile)) { // Try and load a the texture from the file, if not error to the console and exit the program
		std::cerr << "Failed to load texture from file: " << textureFile << std::endl;
		exit(EXIT_FAILURE);
	}
	sprite = new sf::Sprite(*texture); // Create a sprite pointer for the Pixie
	if (!useOriginalOrigin) { // Check if using the original origin, if not set the origin to the center of the sprite
		sprite->setOrigin(getSpriteCenter(*sprite)); // Set the origin of the sprite to the center of the sprite
	}
	sprite->setScale({ DEFAULT_PIXIE_SCALE,DEFAULT_PIXIE_SCALE }); // Set the scale of the sprite to the default Pixie scale
	pixieID = nextPixieID++; // iterate the next Pixie ID and set the Pixie's ID to the current next Pixie ID
	active = true; // Set the Pixie to be active
}

/*
* create(int type, const string& textureFile)
* Params: int type - the type of Pixie to create; const string& textureFile - the file path to the texture to be used for the Pixie
* Desc: Creates and returns a shared pointer of a Pixie and adds it to the static vector of Pixies
*/
shared_ptr<Pixie> Pixie::create(int type, const std::string& textureFile) {
	auto pixie = make_shared<Pixie>(type, textureFile); // Create a shared pointer of a Pixie using the type and texture constructor
	pixies.push_back(pixie); // Add the Pixie to the vector of Pixies
	return pixie; // return the shared pointer of the Pixie
}

/*
* create(int type, const string& textureFile, bool useOriginalOrigin)
* Params: int type - the type of Pixie to create; const string& textureFile - the file path to the texture to be used for the Pixie; bool useOriginalOrigin - whether or not to use the original origin of the sprite (0,0)
* Desc: Creates and returns a shared pointer of a Pixie and adds it to the static vector of Pixies
*/
shared_ptr<Pixie> Pixie::create(int type, const std::string& textureFile, bool useOriginalOrigin) {
	auto pixie = make_shared<Pixie>(type, textureFile, useOriginalOrigin); // Create a shared pointer of a Pixie using the type, texture, and useOriginalOrigin constructor
	pixies.push_back(pixie); // Add the Pixie to the vector of Pixies
	return pixie; // return the shared pointer of the Pixie
}


/*
* ~Pixie()
* Params: None
* Desc: Custom destructor for the Pixie class, Unused
*/
/*Pixie::~Pixie() {
	cout << "Destroying Pixie ID: " << pixieID << endl;
	delete this->sprite;
	delete this->texture;
}*/

// Functions

/*
* draw(RenderWindow& window)
* Params: RenderWindow& window - The game window passed by reference
* Returns: None
* Desc: Draws the pixie onto the window
*/
void Pixie::draw(sf::RenderWindow& window) {
	if (sprite) { // Check if the pixie exists
		window.draw(*sprite); // Draw the pixie's sprite onto the window
	}
}

/*
* isOffScreen()
* Params: None
* Returns: bool
* Desc: Checks if the Pixie is off screen
*/
bool Pixie::isOffScreen() const {
	if (this->sprite) { // Check if the Pixie's Sprite exists
		try { // Try to run the following code
			Vector2f pos = sprite->getPosition(); // Get the Pixie's sprite's position
			return pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT; // Return a boolean based on if the Pixie is within the window bounds 
		}
		catch (const std::exception& e) { // Catch the error if it appears
			return true; // If it errors, assume it is offscreen
		}
	}
	return true; // If the Pixie doesn't exist, assume it is offscreen
}

/*
* isCollidingWith(const Pixie& other)
* Params: Pixie& other - The other Pixie to check if they are colliding
* Returns: bool
* Desc: Checks if two Pixies are colliding
*/
bool Pixie::isCollidingWith(const Pixie& other) const { 
	if (!sprite || !other.sprite) return false; // return false if one or both Pixies do not exist
	if (sprite->getGlobalBounds().findIntersection(other.sprite->getGlobalBounds())) { // Check if the two Pixies intersect
		return true; // Return true if they don't
	}
	return false; // Return false if they do not
}

/*
* drawlAll(RenderWindow& window)
* Params: RenderWindow& window - Window to draw Pixies to
* Returns: None
* Desc: Static function to draw all pixies onto the window
*/
void Pixie::drawAll(RenderWindow& window) {
	for (size_t runInd = 0; runInd < pixies.size(); runInd++) { // Iterate through all the existing Pixies
		if (pixies[runInd].get()) { // Check if the the Pixie exists
			shared_ptr<Pixie> pixie = pixies[runInd]; // Get the Pixie as an object
			if (pixie->isOffScreen()) { // Check if it is offscreen
				continue; // Skip this Pixie if it is offscreen
			}
			if (pixie->pixieType == PIXIE_TYPE_MISSILE) {
				shared_ptr<MissilePixie> missile = dynamic_pointer_cast<MissilePixie>(pixie); // Cast the Pixie to a MissilePixie to access the MissilePixie's specific functions
				if (missile) { // Check if the cast was successful
					cout << "Missile ID: " << missile->getPixieID() << " Owner ID: " << missile->owner->getPixieID() << endl;
					if (Pixie::getPixieByID(missile->owner->getPixieID()) == nullptr) {
						Pixie::removePixieByID(missile->getPixieID()); // Remove the Missile Pixie if the owner doesn't exist
						continue;
					}
				}
			}
			pixie->draw(window); // Draw the Pixie
		}
	}
}

/*
* getPixieByID(RenderWindow& window)
* Params: int ID - ID of Pixie to get
* Returns: shared_ptr<Pixie>
* Desc: returns a Pixie based on a given ID
*/
shared_ptr<Pixie> Pixie::getPixieByID(int ID) {
	for (shared_ptr<Pixie> pixie : Pixie::pixies) { // Iterate through existing Pixies
		if (pixie->pixieID == ID) { // Check if the Pixie's ID matches the given ID
			return pixie; // Return the Pixie
		}
	}
	return nullptr; // Return nullptr if it could not be found
}

/*
* getDirectionTo(const Pixie& other)
* Params: Pixie& other - Other Pixie to get the direction to
* Returns: float
* Desc: returns a radian degree of the direction of the Pixie to the other Pixie
*/
float Pixie::getDirectionTo(const Pixie& other) {
	if (!sprite || !other.sprite) return 0.0f; // Check if the Pixies exist, return 0 if not
	Vector2f direction = other.sprite->getPosition() - sprite->getPosition(); // Direction from the Pixie to the other Pixie
	return atan2(direction.y, direction.x); // Return the radian degree of the direction x and y values
}

/*
* removePixieByID(int ID)
* Params: int ID - ID of Pixie to be removed
* Returns: None
* Desc: Remove a Pixie based on the ID provided
*/
void Pixie::removePixieByID(int ID) {
	auto it = std::find(pixies.begin(), pixies.end(), Pixie::getPixieByID(ID)); // Find the Pixie with getPixieByID and find it in the Pixies vector
	if (it != pixies.end()) { // Check if the Pixie exists
		pixies.erase(it); // Erase the Pixie from the Pixies vectors, automatically deleting it via the shared pointer logic
	}

}

/*
* pixieAtPosition(Vector2f pos)
* Params: Vector2f pos
* Returns: int
* Desc: Get the Pixie ID of a Pixie at a position
*/
int Pixie::pixieAtPosition(Vector2f pos) {
	for (shared_ptr<Pixie> pixie : Pixie::pixies) { // Iterate through the existing Pixies
		if (pixie->pixieType == PIXIE_TYPE_BACKGROUND) { continue; } // If the Pixie is a background pixie then skip it
		if (!pixie->sprite || pixie->sprite == nullptr || pixie->sprite == NULL) { continue; } // Check if the Pixie exists
		if (pixie->sprite->getGlobalBounds().contains(pos)) { // Check if the Pixie exists at the position
			return pixie->pixieID; // Return the Pixie's ID
		}
	} 
	return -1; // Return -1 if no Pixie could be found
}