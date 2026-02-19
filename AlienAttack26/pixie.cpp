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
	sprite->setScale({ DEFAULT_PIXIE_SCALE,DEFAULT_PIXIE_SCALE });
	pixieID = nextPixieID++;
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