#include "gameHeader.h"

int main() {
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!");
	window.setFramerateLimit(60);
	BackgroundPixie background(DEFAULT_BACKGROUND_TEXTURE);
	background.setPosition({ 0, 0 });

	PlayerPixie playerPixie;
	while (window.isOpen()) {
		currentFrame++;
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		playerPixie.update();
		window.clear();
		Pixie::drawAll(window);
		window.display();
		Pixie::deleteOld();
	}
}