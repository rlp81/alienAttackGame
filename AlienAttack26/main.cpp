#include "gameHeader.h"


int currentFrame = 0;

int main() {
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!");
	window.setFramerateLimit(60);
	shared_ptr<BackgroundPixie> background = BackgroundPixie::create(DEFAULT_BACKGROUND_TEXTURE);
	background->setPosition({ 0, 0 });

	shared_ptr<PlayerPixie> playerPixie = PlayerPixie::create();
	playerPixie->setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

	vector<int> swarmMembers;
	shared_ptr<EnemyPixie> leader = EnemyPixie::create(playerPixie->getPixieID());
	leader->setPosition(300, 300);

	shared_ptr<EnemyPixie> enemy;
	swarmMembers.push_back(leader->getPixieID());
	for (int i = 0; i < 20; i++) {
		enemy = EnemyPixie::create(playerPixie->getPixieID());
		swarmMembers.push_back(enemy->getPixieID());

	}
	RayCast ray = RayCast(playerPixie->getPosition(), degrees(90));

	Swarm swarm = Swarm(leader->getPixieID(), swarmMembers);
	while (window.isOpen()) {
		currentFrame++;
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		 
		playerPixie->update();
		swarm.updateSwarm();
		ExplosionPixie::updateAll();
		window.clear();
		Pixie::drawAll(window);
		window.display();
	}
}