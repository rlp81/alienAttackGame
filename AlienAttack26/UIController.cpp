#include "gameHeader.h"

// UI Controller class Functions

UIController::UIController() {
	font.openFromFile(ASSETS_PATH / MAIN_FONT); // Load the font for the UI
	this->scoreText = new Text(font, "Score: 0", TEXT_SIZE);
	scoreText->setPosition(SCORE_POSITION);
	this->healthText = new Text(font, "Health: 10", TEXT_SIZE);
	healthText->setPosition(HEALTH_POSITION);
	this->ammoText = new Text(font, "Ammo: 99", TEXT_SIZE);
	ammoText->setPosition(AMMO_POSITION);
}

void UIController::updateUI(int score, int health, int ammo) {
	stringstream ss;
	ss << "Score: " << score;
	scoreText->setString(ss.str());
	ss.str("");
	ss.clear();
	ss << "Health: " << health;
	healthText->setString(ss.str());
	ss.str("");
	ss.clear();
	ss << "Ammo: " << ammo;
	ammoText->setString(ss.str());
	ss.str("");
	ss.clear();
}

void UIController::draw(RenderWindow& window) {
	window.draw(*scoreText);
	window.draw(*healthText);
	window.draw(*ammoText);
}

void UIController::addDisposableText(const string& text, Vector2f position, int frames) {
	DisposableText::create(*this, text, position, frames);
}

// DisposableText class Functions

vector<shared_ptr<DisposableText>> DisposableText::disposableTexts;

DisposableText::DisposableText(const string& text, Vector2f position, int frames) {
	this->text = new Text(UI_Controller->font, text, TEXT_SIZE);
	this->text->setPosition(position);
	this->lifetime = frames;
	this->createdAt = currentFrame;
	this->deleteAt = createdAt + frames;
}

DisposableText::~DisposableText() {
	delete text; // Clean up the text
}

shared_ptr<DisposableText> DisposableText::create(UIController& controller, const string& text, Vector2f position, int frames) {
	auto temp = make_shared<DisposableText>(text, position, frames);
	disposableTexts.push_back(temp);
	return temp;
}

bool DisposableText::isExpired() const {
	return currentFrame >= deleteAt;
}

void DisposableText::drawAll(RenderWindow& window) {
	for (auto it = disposableTexts.begin(); it != disposableTexts.end();) {
		if ((*it)->isExpired()) {
			it = disposableTexts.erase(it);
		}
		else {
			window.draw(*(*it)->text);
			++it;
		}
	}
}

void DisposableText::draw(RenderWindow& window) {
	window.draw(*text);
}