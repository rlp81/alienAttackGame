#include "gameHeader.h"
int Pixie::nextPixieID = 0;

Pixie::Pixie(int type, const std::string& textureFile) {
	pixieType = type;
	texture = new sf::Texture();
	if (!texture->loadFromFile(textureFile)) {
		std::cerr << "Failed to load texture from file: " << textureFile << std::endl;
		exit(EXIT_FAILURE);
	}
	sprite = new sf::Sprite(*texture);
	sprite->setOrigin(getSpriteCenter(*sprite));
	sprite->setScale({ DEFAULT_PIXIE_SCALE,DEFAULT_PIXIE_SCALE });
	pixieID = nextPixieID++;
	this->pixies.push_back(this);
}

void Pixie::draw(sf::RenderWindow& window) {
	if (sprite) {
		window.draw(*sprite);
	}
}

Pixie::~Pixie() {
	if (texture) {
		delete texture;
		texture = nullptr;
	}
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
	pixieCount--;
}

bool Pixie::isOffScreen() const {
	if (sprite) {
		Vector2f pos = sprite->getPosition();
		return pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT;
	}
	return true;
}

bool Pixie::isCollidingWith(const Pixie& other) const {
	if (!sprite || !other.sprite) return false;
	if (sprite->getGlobalBounds().findIntersection(other.sprite->getGlobalBounds())) {
		return true;
	}
	return false;
}

PlayerPixie::PlayerPixie() : Pixie(1, DEFAULT_SHIP_TEXTURE) {
	setSpeed(DEFAULT_PIXIE_SPEED);
	setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	ammo = DEFAULT_PLAYER_AMMO;
	health = DEFAULT_PIXIE_HEALTH;
	activeMissileCount = 0;
}

void PlayerPixie::shootMissile() {
	if (ammo > 0) {
		MissilePixie* missile = new MissilePixie(this);
		missiles.push_back(missile);
		activeMissileCount++;
		ammo--;
	}
	else {
		std::cout << "Out of ammo!" << std::endl;
	}
}

void::MissilePixie::update() {
	if (owner) {
		float rads = this->getRotation().asRadians();
		double x = cos(rads);
		double y = sin(rads);
		if (abs(x) == 1) {
			this->move(Vector2f(y, x) * -MISSILE_SPEED);
		}
		else if (abs(x) != 1 && abs(y) != 1) {
			if (to_string(x * -1) == to_string(y)) {
				this->move(Vector2f(x, y * -1) * -MISSILE_SPEED);
			}
			else if (to_string(x) == to_string(y)) {
				this->move(Vector2f(x, y * -1) * MISSILE_SPEED);
			}
		}
		else {
			this->move(Vector2f(y, x) * MISSILE_SPEED);
		}

		if (this->isOffScreen()) {
			owner->activeMissileCount--;
			delete this;
		}
		else {
			this->setPosition(owner->getPosition());
		}
	}
	else {
		std::cerr << "Owner not set for MissilePixie!" << std::endl;
	}
}

MissilePixie::MissilePixie(PlayerPixie* owner) : Pixie(2, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED);
	this->owner = owner;
	this->setPosition(owner->getPosition());
	direction = owner->getRotation();
	this->setRotation(direction);
}

bool MissilePixie::checkCollision() {
	for (Pixie* pixie : Pixie::pixies) {
		if (this != pixie && pixie->getPixieID() != owner->getPixieID()) {
			if (this->isCollidingWith(*pixie)) {
				return true;
			}
		}
	}
	return false;
}

void PlayerPixie::update()
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
		this->sprite->setRotation(degrees(-90));
		this->move({ -DISTANCE, 0 });
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		// right arrow is pressed: move our ship right 5 pixels
		yRotation = 90;
		this->move({ DISTANCE, 0 });
		this->setRotation(degrees(90));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)) {
		xRotation = 1;
		this->move({ 0.0, -DISTANCE });
		this->setRotation(degrees(0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)) {
		xRotation = -1;
		this->move({ 0.0, DISTANCE });
		this->setRotation(degrees(180));
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
	this->setRotation(degrees(angle));

	// *** add code (more if/else blocks) to move ship up/dow
	// 
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

void PlayerPixie::updateMissiles(RenderWindow& window) {
	for (MissilePixie* missile : missiles) {
		missile->update();
		missile->draw(window);
	}
}