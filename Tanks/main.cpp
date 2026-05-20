#include <SFML/Graphics.hpp>
#include "Tank.cpp"
#include <unordered_map>


void main() {

	// Create the main window
	sf::RenderWindow window(sf::VideoMode({800, 600}), "Tanks");
	window.setFramerateLimit(60);


	// Map creation
	std::unordered_map<sf::Shape*, sf::Vector2f> Blocks;
	Blocks[new sf::RectangleShape({ 800, -100 })] = { 800, -100 };
	Blocks[new sf::RectangleShape({ -100, 600 })] = { -100, 600 };
	sf::Shape* shape = new sf::RectangleShape({ 800,100 });
	shape->setPosition({ 0,600 });
	Blocks[shape] = { 800, 100 };
	shape = new sf::RectangleShape({ 100,600 });
	shape->setPosition({ 800,0 });
	Blocks[shape] = { 100, 600 };

	// Create a tank object
	Tank player = Tank({400,300});
	player.setBullets(5);
	player.setSize_OF_window({ 800, 600 });
	player.setMap(Blocks);

	// Variable
	int speed = 5;
	sf::Time intervals_BY_SHOOTING = sf::seconds(0.4f);
	sf::Clock shootingTimer;
	sf::Time intervals_BY_RELOADING = sf::seconds(3.5f);
	sf::Clock reloadingTimer;
	bool reloading = false;

	// Fonts and text
	sf::Font font("C:/Windows/Fonts/Arial.ttf");
	
	sf::Text bulletCountText(font, "Bullets: " + std::to_string(player.getBulletCount()), 20);

	// Start the game loop
	while (window.isOpen()) {
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		// Handle input
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
			if (player.getBulletCount() == 0) {
				reloadingTimer.restart();
				reloading = true;
			}
			else if (player.getBulletCount() != 0 &&
				shootingTimer.getElapsedTime() >= intervals_BY_SHOOTING) {
				player.shoot();
				shootingTimer.restart();
			}
		}

		if (reloading && reloadingTimer.getElapsedTime() <= intervals_BY_RELOADING)
		{
			bulletCountText.setString("Reloading..."+ std::to_string((int)(4-reloadingTimer.getElapsedTime().asSeconds())));

		}
		else
		{
			bulletCountText.setString("Bullets: " + std::to_string(player.getBulletCount()));
			reloadingTimer.stop();
		}
		if (reloading && reloadingTimer.getElapsedTime() > intervals_BY_RELOADING)
		{
			player.reload();
			reloading = false;
		}

		player.updateBullets(speed);

		window.clear(sf::Color(115,115 ,115,255));
		window.draw(player);
		for (const auto& bullet : player.getBullets()) {
			window.draw(bullet);
		}
		window.draw(bulletCountText);
		window.display();
	} // End of game loop
}