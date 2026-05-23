#include <SFML/Graphics.hpp>
#include "Tank.cpp"
#include <unordered_map>
#include "Buttens.cpp"


sf::Shape* createWall(sf::Shape* shape, sf::Vector2f coordinate) {
	shape->setPosition(coordinate);
	shape->setFillColor(sf::Color::Yellow);
	return shape;
}

void main() {

	// Create the main window
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Tanks");
	window.setFramerateLimit(60);


	// Map creation
	std::unordered_map<sf::Shape*, sf::Vector2f> Blocks;
	Blocks[new sf::RectangleShape({ 800, -100 })] = { 800, -100 };
	Blocks[new sf::RectangleShape({ -100, 600 })] = { -100, 600 };
	Blocks[createWall(new sf::RectangleShape({ 800,100 }), { 0, 600 })] = { 800, 100 };
	Blocks[createWall(new sf::RectangleShape({ 100,600 }), { 800, 0 })] = { 100, 600 };
	Blocks[createWall(new sf::RectangleShape({ 300, 10 }), { 0, 120 })] = { 300, 10 };
	Blocks[createWall(new sf::RectangleShape({ 10, 100 }), { 200, 120 })] = { 10, 100 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 15, 300 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 400, 120 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 500, 220 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 500, 220 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 500, 520 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 100, 390 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 80, 10 }), { 700, 490 })] = { 20, 10 };
	Blocks[createWall(new sf::RectangleShape({ 10, 80 }), { 780, 490 })] = { 10, 20 };
	Blocks[createWall(new sf::RectangleShape({ 10, 80 }), { 180, 390 })] = { 10, 20 };

	// Create a tank object
	Tank player = Tank({ 400,300 });
	player.setBullets(5);
	player.setSize_OF_window({ 800, 600 });
	player.setMap(Blocks);

	Tank player2 = Tank({ 600, 200 });
	player2.setColor(sf::Color::Red);
	player2.setBullets(5);
	player2.setSize_OF_window({ 800, 600 });
	player2.setMap(Blocks);

	// Variable
	int speed = 5;
	sf::Time intervals_BY_SHOOTING = sf::seconds(0.4f);
	sf::Clock shootingTimer;
	sf::Clock shootingTimer2;
	sf::Time intervals_BY_RELOADING = sf::seconds(3.5f);
	sf::Clock reloadingTimer;
	sf::Clock reloadingTimer2;
	bool reloading = false;
	bool player2InGame = false;
	bool player2_Reloading = false;
	bool isStart = false;

	// Fonts and text
	sf::Font font("C:/Windows/Fonts/Arial.ttf");

	sf::Text bulletCountText(font, "Bullets: " + std::to_string(player.getBulletCount()), 20);
	sf::Text bulletCountText2(font, "Bullets p2: " + std::to_string(player2.getBulletCount()), 20);

	Buttens startButten({ 600.f, 100.f }, {100.f, 100.f}, (char*)"Play", font, sf::Color::Green);
	Buttens PlayOnlineButten({ 600.f, 100.f }, { 100.f, 250.f }, (char*)"Play Online", font, sf::Color::Green);
	Buttens ExitButten({ 600.f, 100.f }, { 100.f, 400.f }, (char*)"Exit", font, sf::Color::Green);

	bulletCountText2.setPosition({ 600, 0 });
	// Start the game loop
	while (window.isOpen()) {
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !player2InGame) {
				player2InGame = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
				player.setAlive(true);
				player2.setAlive(true);
			}
		}

		// Handle input
		if (player.isAlive()) {
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !reloading) {
				if (player.getBulletCount() == 0) {
					reloadingTimer.restart();
					reloading = true;
				}
				else if (player.getBulletCount() != 0 &&
					shootingTimer2.getElapsedTime() >= intervals_BY_SHOOTING) {
					player.shoot();
					shootingTimer2.restart();
				}
			}
		}

		// Player2 controlers
		if (player2InGame && player2.isAlive()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
				player2.move(speed);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
				player2.move(-speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
				player2.rotate(-5);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
				player2.rotate(5);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !player2_Reloading) {
				if (player2.getBulletCount() == 0) {
					reloadingTimer2.restart();
					player2_Reloading = true;
				}
				else if (player2.getBulletCount() != 0 &&
					shootingTimer2.getElapsedTime() >= intervals_BY_SHOOTING) {
					player2.shoot();
					shootingTimer2.restart();
				}
			}
			if (player2_Reloading && reloadingTimer2.getElapsedTime() <= intervals_BY_RELOADING)
			{
				bulletCountText2.setString("Reloading..." + std::to_string((int)(4 - reloadingTimer2.getElapsedTime().asSeconds())));

			}
			else
			{
				bulletCountText2.setString("Bullets p2: " + std::to_string(player2.getBulletCount()));
				reloadingTimer2.stop();
			}
			if (player2_Reloading && reloadingTimer2.getElapsedTime() > intervals_BY_RELOADING)
			{
				player2.reload();
				player2_Reloading = false;
			}

			player2.updateBullets(speed);
			player2.collisionWithBullet(player.getBullets());

		}

		if (reloading && reloadingTimer.getElapsedTime() <= intervals_BY_RELOADING)
		{
			bulletCountText.setString("Reloading..." + std::to_string((int)(4 - reloadingTimer.getElapsedTime().asSeconds())));

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
		player.collisionWithBullet(player2.getBullets());

		window.clear(sf::Color(115, 115, 115, 255));
		if (isStart) {
			window.draw(player);
			if (player2InGame) {
				window.draw(player2);
				for (const auto& bullet : player2.getBullets()) {
					window.draw(bullet);
				}
				window.draw(bulletCountText2);
			}
			for (const auto& bullet : player.getBullets()) {
				window.draw(bullet);
			}
			for (const auto& pair : Blocks) {
				window.draw(*pair.first);
			}
			window.draw(bulletCountText);
		}
		else {
			window.draw(startButten);
			window.draw(PlayOnlineButten);
			window.draw(ExitButten);
			if (startButten.click((sf::Vector2f)sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				isStart = true;
			}
			else if (PlayOnlineButten.click((sf::Vector2f)sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				// Online play functionality can be implemented here
			}
			else if (ExitButten.click((sf::Vector2f)sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				window.close();
			}
		}
		window.display();
	} // End of game loop
}