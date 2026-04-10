#include "gameHeader.h"


vector<int> ExplosionPixie::explosionPixies;
ExplosionPixie::ExplosionPixie(const string& baseTextureFile, int textureNums) : Pixie(PIXIE_TYPE_EXPLOSION) {
	lastFrame = currentFrame+EXPLOSION_FRAMES;
	startFrame = currentFrame;
	this->baseTextureFile = baseTextureFile;
	spriteNum = 0;
	sprite = nullptr;
	scaleIncrement = 0.1f;
	currentScale = 1.0f;
	increment = 1;
}

ExplosionPixie::ExplosionPixie(const string& baseTextureFile, int textureNums, sf::Vector2f& position) : Pixie(4) {
	lastFrame = currentFrame + EXPLOSION_FRAMES;
	this->posX = position.x;
	this->posY = position.y;
	startFrame = currentFrame;
	this->baseTextureFile = baseTextureFile;
	this->textureNums = textureNums;
	spriteNum = 0;
	scaleIncrement = 0.1f;
	currentScale = 1.0f;
	increment = 1;
}


shared_ptr<ExplosionPixie> ExplosionPixie::create(int textureAmount, const string& textureFile, sf::Vector2f position) {
	auto explosion = make_shared<ExplosionPixie>(textureFile, textureAmount, position);
	pixies.push_back(explosion);
	explosionPixies.push_back(explosion->getPixieID());
	return explosion;
}

shared_ptr<ExplosionPixie> ExplosionPixie::create(int textureAmount, const string& textureFile) {
	auto explosion = make_shared<ExplosionPixie>(textureFile, textureAmount);
	pixies.push_back(explosion);
	explosionPixies.push_back(explosion->getPixieID());
	return explosion;
}

void ExplosionPixie::updateAll() {
	for (int expId: explosionPixies) {
		shared_ptr<ExplosionPixie> exp = dynamic_pointer_cast<ExplosionPixie>(Pixie::getPixieByID(expId));
		if (exp) {
			exp->update();
		}
	}
}

void ExplosionPixie::update() {
	if (currentFrame >= lastFrame) {
		this->removePixieByID(this->getPixieID());
		return;
	}
	else {
		int frame = (currentFrame - startFrame);
		if (frame % NEXT_EVERY_FRAME == 0) {
			spriteNum += increment;
			if (spriteNum >= textureNums) {
				increment = -1;
				scaleIncrement *= -1;
				spriteNum = 3;
			}
			if (spriteNum <= 0) {
				this->removePixieByID(this->getPixieID());
				return;
			}
			string textureFile = baseTextureFile + to_string(spriteNum) + ".png";
			texture = new Texture();
			if (!texture->loadFromFile(ASSETS_PATH/textureFile)) {
				std::cerr << "Failed to load texture from file: " << textureFile << std::endl;
				exit(EXIT_FAILURE);
			}
			if (sprite != nullptr) {
				delete sprite;
			}
			sprite = new Sprite(*texture);
			sprite->setOrigin(getSpriteCenter(*sprite));
			sprite->setPosition({ posX, posY });
		}
	}
	if (spriteNum <= textureNums) {
		setScale(currentScale, currentScale);
		currentScale += scaleIncrement;
	}
}

bool ExplosionPixie::isFinished() { 
	return lastFrame >= currentFrame; 
}