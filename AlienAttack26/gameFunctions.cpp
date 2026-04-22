#include "gameHeader.h"
/*
*  gameFunctions.cpp
*     - The functions for the game program are in this file. 
* 
*  AUTHOR: Most of the work in this program was completed by Prof. Andy Harbert
*          Prof. Pat Smith has made modifications (December 2021)
*		   Cole lehl
*
*/

// Declare Global Variables
int lastPixieDumpFrame = 0; // Last frame to dump deleted Pixies, deprecated
int playerID = -1; // Stored ID of the Player
int playerScore = 0; // Score of the Player
UIController* UI_Controller = nullptr; // The UIController for the game, used to manage the UI elements of the game

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

/*
*  DEPRECATED
*  updateShip(Sprite& ship)
*  Params: Sprite& ship - Sprite to update
*  Return: None
*  Desc: Updates the player ship based on player input
*/
void updateShip(Sprite& ship)
{
	/*
	 *  This first If-then-else-if Block handles 
	 */
	int xRotation = 0;
	int yRotation = 0;
	int angle = 0;

	/*
	 *  This first If-then-else-if Block handles
	 */
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		// left arrow is pressed: move our ship left 5 pixels ( this is -5 pixels to go left)
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		yRotation = -90;
		ship.setRotation(degrees(-90));
		ship.move({ -DISTANCE, 0 });
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		// right arrow is pressed: move our ship right 5 pixels
		yRotation = 90;
		ship.move({ DISTANCE, 0 });
		ship.setRotation(degrees(90));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)) {
		xRotation = 1;
		ship.move({ 0.0, -DISTANCE });
		ship.setRotation(degrees(0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)) {
		xRotation = -1;
		ship.move({ 0.0, DISTANCE });
		ship.setRotation(degrees(180));
	}

	if (xRotation != 0) {
		switch (yRotation) {
		case -90:
			angle = -45;
			if (xRotation < 0)
				angle = -135;
			break;
		case 90:
			angle = 45;
			if (xRotation < 0)
				angle = 135;
			break;
		default:
			switch (xRotation)
			{
			case(-1):
				angle = 180;
				break;
			default:
				angle = 0;
				break;
			}
		}
	}
	else {
		angle = yRotation;
	}
	ship.setRotation(degrees(angle));

	// *** add code (more if/else blocks) to move ship up/down

	int locationX = static_cast<int>(ship.getPosition().x);
	int locationY = static_cast<int>(ship.getPosition().y);
	// What do you want to do when you reach the edge of the screen? 
	//   You might just move the ship back, simulate hitting a "wall"
	//   You might also wrap around (change from some value greater than
	//   the width of the window back to zero, or from some x value less
	//   than zero to something like 795, near the far right edge? 
	//  Or you could do nothing? 
	// This statement gets the ship's x location. If you decide you want 
	//   to do something with the problem of the ship moving off screen
	//   you can use this:
	//
	//        ship.setPosition(float x, float y); 
	// 
	//   You pass the setPosition method the x and y value you want 
	//     to set the ship at. 
	
	// If you're having trouble, using this command will display the
	// position of the ship every time you enter this function!
	// 
	//cout << ship.getPosition().x << ", " << ship.getPosition().y << endl; 
}


/*
* getSpriteCenter(const Sprite& sprite)
* Params: Sprite& sprite - the sprite to get the center position of
* Returns: Vector2f
* Desc: Returns the center position of the sprite
*/
Vector2f getSpriteCenter(const Sprite& sprite)
{
	FloatRect bounds = sprite.getGlobalBounds(); // The bounds of the sprite
	return Vector2f(bounds.size.x / 2.0f, bounds.size.y / 2.0f); // Returns the center x and y position in vector2f
}

/*
* getSpriteCenterPosition(const Sprite& sprite)
* Params: Sprite& sprite - the sprite to get the center position of
* Returns: Vector2f
* Desc: Returns the center position of the sprite in terms
*/
Vector2f getSpriteCenterPosition(const Sprite& sprite)
{
	return sprite.getPosition() + getSpriteCenter(sprite); // Add global and local position
}

/*
* getSpriteCenterPosition(const Sprite& sprite)
* Params: Sprite& sprite - the sprite to get the center position of
* Returns: Vector2f
* Desc: Returns the center position of the sprite in terms
*/
Vector2f getSpriteTopCenterPosition(const Sprite& sprite)
{
	FloatRect bounds = sprite.getGlobalBounds(); // Get sprite position bounds
	return sprite.getPosition() + Vector2f(bounds.size.x / 2.0f, 0.0f); // Get the top center of the position
}

/*
* setSpriteCenterPosition(const Sprite& sprite)
* Params: Sprite& sprite - the sprite to set the center position of
* Returns: None
* Desc: Sets the center position of the sprite in terms
*/
void setSpriteCenterPosition(Sprite& sprite, Vector2f centerPosition)
{
	sprite.setPosition(centerPosition - getSpriteCenter(sprite)); // Set the position of the sprite to the given center
}

/*
* isSpriteOffScreen(const Sprite& sprite)
* Params: Sprite& sprite - the sprite to get the center position of
* Returns: bool
* Desc: Returns if the sprite is off screen
*/
bool isSpriteOffScreen(const Sprite& sprite)
{
	Vector2f position = sprite.getPosition();  // Get the position of the sprite
	FloatRect bounds = sprite.getGlobalBounds(); // get the bounds of the sprite
	return position.x + bounds.size.x < 0 || position.x > WINDOW_WIDTH || // Return if the screen is off screen
		position.y + bounds.size.y < 0 || position.y > WINDOW_HEIGHT;
}

/*
* loadTexture(const string& fileName)
* Params: string& fileName - file name of the texture to load
* Returns: Texture
* Desc: Returns a texture for a sprite to load
*/
Texture loadTexture(const string& fileName)
{
	Texture texture; // Create the texture variable
	if (!texture.loadFromFile(fileName)) // Try and load the texture from the file name, if it fails output an error and exit the program
	{
		cout << "Unable to load texture from file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	return texture; // Return the texture
}

/*
* loadTextureAsPointer(const string& fileName)
* Params: string& fileName - file name of the texture to load
* Returns: Texture*
* Desc: Returns a texture for a sprite to load as a pointer
*/
Texture* loadTextureAsPointer(const string& fileName)
{
	Texture* texture = new Texture(); // Create a new texture as a pointer
	if (!texture->loadFromFile(fileName)) // Try and load the texture from the file name, if it fails output an error and exit the program
	{
		cout << "Unable to load texture from file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	return texture; // Return the texture as a pointer
}

/*
* checkCollision(const Sprite& sprite, Sprite& sprite2)
* Params: Sprite& sprite1 - the 1st sprite to check for collision; Sprite& sprite2 - the 2nd sprite to check for collision 
* Returns: bool
* Desc: Returns if the two sprites are collisions
*/
bool checkCollision(const Sprite& sprite1, const Sprite& sprite2) {
	if (!(&sprite1 && &sprite2) || &sprite1 == &sprite2) { // Check if the two sprites don't exist and if they are the same
		return false; // return false 
	}
	
	FloatRect sBounds1 = sprite1.getGlobalBounds(); // First Sprite's bounds
	FloatRect sBounds2 = sprite2.getGlobalBounds(); // Second Sprite's bounds
	bool result = false; // The result
	if (sBounds1.findIntersection(sBounds2)) // Check if the two sprite's intersect
	{
		result = true; // Set the result to true
	}
	return result; // return the result
}
