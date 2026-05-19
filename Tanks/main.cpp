#include <SFML/Graphics.hpp>
#include "Tank.cpp"


void main() {

	// Create the main window
	sf::RenderWindow window(sf::VideoMode({800, 600}), "Tanks");
	window.setFramerateLimit(60);
	sf::RectangleShape background;
	background.setSize({ 800, 600 });


	// Create a tank object
	Tank player = Tank({400,300});
	player.setBullets(5);
	player.setSize_OF_window({ 800, 600 });
	

	// Constants
	int speed = 5;
	int timer = 0;
	sf::Time intervals_BY_SHOOTING = sf::seconds(0.2f);
	sf::Clock shootingTimer;
	sf::Time intervals_BY_RELOADING = sf::seconds(1.5f);
	sf::Clock reloadingTimer;
	
	// Start the game loop
	while (window.isOpen()) {
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		timer++;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(-speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.rotate(-5);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.rotate(5);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			if (player.getBulletCount() == 0 &&
				reloadingTimer.getElapsedTime() >= intervals_BY_RELOADING) {
				player.reload();
			}
			else if (player.getBulletCount() != 0 &&
				shootingTimer.getElapsedTime() >= intervals_BY_SHOOTING) {
				player.shoot();
				reloadingTimer.restart();
				shootingTimer.restart();
			}
		}

		player.updateBullets(speed, background);

		window.clear(sf::Color::Black);
		window.draw(player);
		for (const auto& bullet : player.getBullets()) {
			window.draw(bullet);
		}
		window.display();
	} // End of game loop
}