#include "gameHeader.h"
int currentFrame = 0;
int lastPixieDumpFrame = 0;
int playerID = -1;
/*
*  gameFunctions.cpp
*     - The functions for the game program are in this file. 
* 
*  AUTHOR: Most of the work in this program was completed by Prof. Andy Harbert
*          Prof. Pat Smith has made modifications (December 2021)
*
*/

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

/*
*  moveShip - This function is called to handle a keyPress event. 
*     Keyboard input is detected and ship is moved.
*   ** Part of the lab is to also handle firing a missile **
*  INPUT: The ship sprite is passed.  This merely a drawn object on the screen.
*  RETURN: None
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

Vector2f getSpriteCenter(const Sprite& sprite)
{
	FloatRect bounds = sprite.getGlobalBounds();
	return Vector2f(bounds.size.x / 2.0f, bounds.size.y / 2.0f);
}

Vector2f getSpriteCenterPosition(const Sprite& sprite)
{
	return sprite.getPosition() + getSpriteCenter(sprite);
}

Vector2f getSpriteTopCenterPosition(const Sprite& sprite)
{
	FloatRect bounds = sprite.getGlobalBounds();
	return sprite.getPosition() + Vector2f(bounds.size.x / 2.0f, 0.0f);
}

void setSpriteCenterPosition(Sprite& sprite, Vector2f centerPosition)
{
	sprite.setPosition(centerPosition - getSpriteCenter(sprite));
}

bool isSpriteOffScreen(const Sprite& sprite)
{
	Vector2f position = sprite.getPosition();
	FloatRect bounds = sprite.getGlobalBounds();
	return position.x + bounds.size.x < 0 || position.x > WINDOW_WIDTH ||
		position.y + bounds.size.y < 0 || position.y > WINDOW_HEIGHT;
}

Texture loadTexture(const string& fileName)
{
	Texture texture;
	if (!texture.loadFromFile(fileName))
	{
		cout << "Unable to load texture from file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	return texture;
}

Texture* loadTextureAsPointer(const string& fileName)
{
	Texture* texture = new Texture();
	if (!texture->loadFromFile(fileName))
	{
		cout << "Unable to load texture from file: " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	return texture;
}

bool checkCollision(const Sprite& sprite1, const Sprite& sprite2) {
	if (!(&sprite1 && &sprite2) || &sprite1 == &sprite2) {
		return false;
	}
	
	FloatRect sBounds1 = sprite1.getGlobalBounds();
	FloatRect sBounds2 = sprite2.getGlobalBounds();
	bool result = false;
	if (sBounds1.findIntersection(sBounds2))
	{
		result = true;
	}
	return result;
}

/*void newAlien() {
	Alien* newAlien = new Alien("Blorg");
	newAlien->setPosition(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
	//aliens.push_back(newAlien);
}*/
