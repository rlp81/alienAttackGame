#pragma once
#include "gameHeader.h"

const int TEXT_SIZE = 20; // Default text size for the UI
const Vector2f SCORE_POSITION = { 10.0f, 10.0f }; // Position of the score text on the UI
const Vector2f HEALTH_POSITION = { 10.0f, 40.0f }; // Position of the health text on the UI
const Vector2f AMMO_POSITION = { 10.0f, 70.0f }; // Position of the ammo text on the UI


class UIController {
private:
	friend class DisposableText;
	Font font; // Font used for the UI
	sf::Text* scoreText; // Text to display the player's score
	sf::Text* healthText; // Text to display the player's health
	sf::Text* ammoText; // Text to display the player's ammo
public:
	UIController();
	~UIController() {
		delete scoreText; // Clean up the score text
		delete healthText; // Clean up the health text
		delete ammoText; // Clean up the ammo text
	}
	void updateUI(int score, int health, int ammo); // Update the UI with the current score, health, and ammo
	void draw(RenderWindow& window); // Draw the UI to the window
	void addDisposableText(const string& text, Vector2f position, int frames); // Add a temporary text to the UI that disappears after a short time
};

class DisposableText {
private:
	friend class UIController;
	static vector<shared_ptr<DisposableText>> disposableTexts; // Vector of temporary texts that will be displayed on the UI
	Text* text; // The text to be displayed
	int lifetime;
	int createdAt;
	int deleteAt;
public:
	DisposableText(const string& text, Vector2f position, int frames); // Constructor for the DisposableText class
	static shared_ptr<DisposableText> create(UIController& controller, const string& text, Vector2f position, int frames); // Static function to create a shared pointer of a DisposableText
	~DisposableText();
	static void drawAll(RenderWindow& window);
	bool isExpired() const; // Check if the DisposableText has expired based on the current frame
	void draw(RenderWindow& window); // Draw the DisposableText to the window
};