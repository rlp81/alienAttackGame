#include "gameHeader.h"
int Pixie::nextPixieID = 0;
int Pixie::pixieCount = 0;
vector<std::shared_ptr <Pixie>> Pixie::pixies;

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
}


void Pixie::draw(sf::RenderWindow& window) {
	if (sprite) {
		window.draw(*sprite);
	}
}

shared_ptr<Pixie> Pixie::create(int type, const std::string& textureFile) {
	auto pixie = make_shared<Pixie>(type, textureFile);
	pixies.push_back(pixie);
	return pixie;
}

shared_ptr<Pixie> Pixie::create(int type, const std::string& textureFile, bool useOriginalOrigin) {
	auto pixie = make_shared<Pixie>(type, textureFile, useOriginalOrigin);
	pixies.push_back(pixie);
	return pixie;
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


void Pixie::drawAll(RenderWindow& window) {
	for (size_t runInd = 0; runInd < pixies.size(); runInd++) {
		if (pixies[runInd].get()) {
			if (pixies[runInd].get()->isOffScreen()) {
				continue;
			}
			pixies[runInd].get()->draw(window);
		}
	}
}