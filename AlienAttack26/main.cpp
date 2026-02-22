#include "gameHeader.h"


int currentFrame = 0;

int main() {
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!");
	window.setFramerateLimit(60);
	shared_ptr<BackgroundPixie> background = BackgroundPixie::create(DEFAULT_BACKGROUND_TEXTURE);
	background->setPosition({ 0, 0 });

	shared_ptr<PlayerPixie> playerPixie = PlayerPixie::create();
	playerPixie->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

	shared_ptr<EnemyPixie> enemyPixie = EnemyPixie::create(playerPixie->getPixieID());

	while (window.isOpen()) {
		currentFrame++;
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		playerPixie->update();
		enemyPixie->update();
		ExplosionPixie::updateAll();
		window.clear();
		Pixie::drawAll(window);
		window.display();
	}
}