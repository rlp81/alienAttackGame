#include "gameHeader.h"
int Pixie::nextPixieID = 0;
int Pixie::pixieCount = 0;
vector<std::unique_ptr<Pixie>> Pixie::pixies;
vector<int> Pixie::deletedPixies;

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
	active = true;
	pixies.push_back(std::make_unique<Pixie>(*this));
}

Pixie::Pixie(int type, const std::string& textureFile, bool useOriginalOrigin) {
	pixieType = type;
	texture = new sf::Texture();
	if (!texture->loadFromFile(textureFile)) {
		std::cerr << "Failed to load texture from file: " << textureFile << std::endl;
		exit(EXIT_FAILURE);
	}
	sprite = new sf::Sprite(*texture);
	if (!useOriginalOrigin) {
		sprite->setOrigin(getSpriteCenter(*sprite));
	}
	sprite->setScale({ DEFAULT_PIXIE_SCALE,DEFAULT_PIXIE_SCALE });
	pixieID = nextPixieID++;
	active = true;
	pixies.push_back(std::make_unique<Pixie>(*this));
}

bool Pixie::checkIfActive() {
	for (const auto& pixie : pixies) {
		if (pixie->getPixieID() == pixieID) {
			if (find(deletedPixies.begin(), deletedPixies.end(), pixieID) != deletedPixies.end()) {
				return false;
			}
			return true;
		}
	}
	return false;
}

void Pixie::draw(sf::RenderWindow& window) {
	if (sprite&&checkIfActive()) {
		cout << "Pixie ID: " << pixieID << " is being drawn.\n";
		window.draw(*sprite);
	}
}

Pixie::~Pixie() {
	pixieCount--;
	if (!active) {
		return;
	}
	active = false;
	cout << "Destroying Pixie\n";
	if (texture) {
//		delete texture;
	//	texture = nullptr;
	}
	if (sprite) {
		//delete sprite;
		//sprite = nullptr;
	}
}

bool Pixie::isOffScreen() const {
	if (this->sprite) {
		try {
			Vector2f pos = sprite->getPosition();
			return pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT;
		}
		catch (const std::exception& e) {
			return true;
		}
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
	lastMissileFrame = -1;
}

void PlayerPixie::shootMissile() {
	if (!(currentFrame >= DEFAULT_FRAMES_TILL__NEXT_MISSILE + lastMissileFrame || lastMissileFrame == -1)) {
		return;
	}
	if (activeMissileCount >= MAX_ACTIVE_MISSILES) {
		std::cout << "Maximum active missiles reached!" << std::endl;
		return;
	}
	if (ammo > 0) {
		cout << "Shooting missile! Ammo left: " << ammo << endl;
		lastMissileFrame = currentFrame;
		MissilePixie* missile = new MissilePixie(this);
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
	}
	else {
		std::cerr << "Owner not set for MissilePixie!" << std::endl;
	}
}

void MissilePixie::remove() {
	/*deletedPixies.push_back(this->getPixieID());
	owner->missiles.erase(std::remove(owner->missiles.begin(), owner->missiles.end(), this), owner->missiles.end());
	pixies.erase(std::remove(pixies.begin(), pixies.end(), this), pixies.end());
	owner->activeMissileCount--;*/
}

MissilePixie::MissilePixie(PlayerPixie* owner) : Pixie(2, DEFAULT_MISSILE_TEXTURE) {
	setSpeed(DEFAULT_MISSILE_SPEED);
	this->owner = owner;
	this->setPosition(owner->getPosition());
	direction = owner->direction;
	this->setRotation(degrees(direction));
	owner->missiles.push_back(unique_ptr<MissilePixie>(this));
}

bool MissilePixie::checkCollision() {
	for (const auto& pixie : Pixie::pixies) {
		if (this->getPixieID() != pixie->getPixieID() && pixie->getPixieID() != owner->getPixieID()) {
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
	
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		this->shootMissile();
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
	this->direction = angle;
	updateMissiles();
}

void PlayerPixie::updateMissiles() {
	for (const auto& missile : missiles) {
		if (missile)
		{ 
			missile->update(); 
			if (missile->isOffScreen()) {
				cout << pixies.size() << endl;
				deletedPixies.push_back(missile->getPixieID());
				size_t index = missile->getPixieID();
				missiles.erase(std::remove(missiles.begin(), missiles.end(), missile), missiles.end());
				pixies.erase(pixies.begin()+index);
				//pixies.erase(std::remove(pixies.begin(), pixies.end(), &missile), pixies.end());
				//delete &missile;
				cout << pixies.size() << endl;
				this->activeMissileCount--;
			}
		}
		else {
			missiles.erase(std::remove(missiles.begin(), missiles.end(), missile), missiles.end());
		}
	}
}

void Pixie::drawAll(RenderWindow& window) {
	for (const auto& pixie : pixies) {
		if (pixie->isOffScreen()) {
			continue;
		}
		pixie->draw(window);
	}
}

void Pixie::deleteOld() {
	if (lastPixieDumpFrame + DUMP_PIXIES_EVERY < currentFrame) {
		if (deletedPixies.size() > 2) {
			deletedPixies.erase(deletedPixies.begin(), deletedPixies.end() - 2);
		}
		lastPixieDumpFrame = currentFrame;
	}
}