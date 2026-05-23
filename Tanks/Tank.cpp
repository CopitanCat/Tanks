#include <SFML/Graphics.hpp>
#include "Bullet.cpp"
#include <iostream>

class Tank : public sf::Drawable {
private:
    sf::RectangleShape tankBody;
    sf::Texture tanksTexture;
	sf::Vector2f coordinates;
    sf::Vector2f size;
    sf::Vector2f size_OF_window;
	sf::Angle angle = tankBody.getRotation()- sf::degrees(90);
	std::vector<Bullet> bullets;
	int bulletCount = 0;
	std::unordered_map<sf::Shape*, sf::Vector2f> Map;
	sf::Vector2f lastPosition;
	sf::Time BulletDuration = sf::seconds(5.f);
	bool Alive = true;

public:
	// Constructors
    Tank() {
		coordinates = {20, 20 };
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
    Tank(sf::Vector2f coordinates) {
		this->coordinates = coordinates;
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
		std::cout << tankBody.getRotation().asDegrees() << std::endl;
    }
    Tank(sf::Color color) {
		coordinates = {20, 20 };
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
    Tank(sf::Vector2f coordinate , sf::Color color) {
		this->coordinates = coordinates;
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
	Tank(sf::Vector2f coordinate, sf::Vector2f size) {
		this->coordinates = coordinates;
		this->size = size;
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
	}
	Tank(sf::Vector2f coordinate, sf::Color color, sf::Vector2f size) {
		this->coordinates = coordinates;
		this->size = size;
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
	}
	Tank(sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		coordinates = {20, 20 };
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
	}
	Tank(sf::Vector2f coordinates, sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		this->coordinates = coordinates;
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
    Tank(sf::Color color, sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		coordinates = {20, 20 };
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
    Tank(sf::Vector2f coordinate , sf::Color color, sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		this->coordinates = coordinates;
		size = { 20, 40 };
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
    }
	Tank(sf::Vector2f coordinate, sf::Vector2f size, sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		this->coordinates = coordinates;
		this->size = size;
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(sf::Color::Green);
		tankBody.setOrigin({size.x /2 , size.y /2});
	}
	Tank(sf::Vector2f coordinate, sf::Color color, sf::Vector2f size, sf::Texture texture) {
		tanksTexture = texture;
		tankBody.setTexture(&tanksTexture);
		this->coordinates = coordinates;
		this->size = size;
		tankBody.setPosition(coordinates);
		tankBody.setSize(size);
		tankBody.setFillColor(color);
		tankBody.setOrigin({size.x /2 , size.y /2});
	}

	//setters
	void setSize_OF_window(sf::Vector2f size_OF_window) {
		this->size_OF_window = size_OF_window;
	}

	void setBullets(int count) {
		bulletCount = count;
	}

	void setMap(std::unordered_map<sf::Shape*, sf::Vector2f> map) {
		Map = map;
	}

	void setDuration_BY_Bullet(sf::Time duration) {
		BulletDuration = duration;
	}
	
	void setColor(sf::Color color) {
		tankBody.setFillColor(color);
	}

	void setAlive(bool alive) {
		Alive = alive;
	}

	// getters

	std::vector<Bullet>& getBullets() {
		return bullets;
	}

	int getBulletCount() {
		return bulletCount;
	}

	bool isAlive() {
		return Alive;
	}

	// Actions
	void move(float speed) {
		if (checkCollision()) {
			tankBody.move({ -speed * std::cos(angle.asRadians()), -speed * std::sin(angle.asRadians())});
		}
		else {
			tankBody.move({ speed * std::cos(angle.asRadians()), speed * std::sin(angle.asRadians()) });
			lastPosition = tankBody.getPosition();
		}
	}

	void rotate(float angle) {
		tankBody.rotate(sf::degrees(angle));
		this->angle += sf::degrees(angle);
		std::cout << tankBody.getRotation().asDegrees() << std::endl;
	}

	void shoot() {
		coordinates = tankBody.getPosition();
		if (bulletCount > 0) {
			bullets.push_back(Bullet({coordinates.x + cos(angle.asRadians())*((size.x)+8), coordinates.y + sin(angle.asRadians())*((size.y)+8)}));
			bullets.back().setAngle(angle);
			bullets.back().setLiveTime(BulletDuration);
			bulletCount--;
		}
	
	}

	void updateBullets(float speed) {
		for (auto& bullet : bullets) {
			bool hit = BulletBoundColision(bullet, Map);
			bullet.move(speed * 1.3, hit);
		}
		removeDeadBullets();
	}



	void reload() {
		bulletCount = 5;
	}


	// Collision Detection
	bool checkCollision() {
		for (const auto& pair : Map) {
			if (tankBody.getGlobalBounds().findIntersection(pair.first->getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}


	void collisionWithBullet(std::vector<Bullet> bullets) {
		for (Bullet bullet : bullets) {
			if (bullet.getShape().getGlobalBounds().findIntersection(tankBody.getGlobalBounds())){
				Alive = false;
				break;
			}
		}
	}

	bool BulletBoundColision(Bullet& bullet, const std::unordered_map<sf::Shape*, sf::Vector2f> map) {
		for (auto [s, v] : map) {
			if (bullet.checkCollision(s)) {
				bullet.setSize(v);
				return true;
			}
		}
		return false;
	}



private:

	void removeDeadBullets() {
		std::vector<Bullet> aliveBullets;
		for (Bullet bullet : bullets) {
			if (bullet.isAlive()) {
				aliveBullets.push_back(bullet);
			}
		}
		bullets = aliveBullets;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		sf::Clock explodeClock;
		sf::Time explodeDuration = sf::seconds(3.f);
		if (Alive) {
			sf::CircleShape top(size.x/3);
			top.setFillColor(sf::Color::Black);
			sf::RectangleShape barrel({ size.x / 4, size.y / 2 });
			barrel.setFillColor(sf::Color::Black);
			barrel.setOrigin({ barrel.getSize().x / 2, barrel.getSize().y });
			top.setOrigin({ top.getRadius(), top.getRadius() });
			top.setPosition(tankBody.getPosition());
			barrel.setPosition(tankBody.getPosition());
			barrel.setRotation(tankBody.getRotation());
			target.draw(tankBody, states);
			target.draw(top, states);
			target.draw(barrel, states);
			explodeClock.restart();
		}
		else {
			sf::CircleShape explosion(size.x/2);
			explosion.setFillColor(sf::Color::Red);
			explosion.setOrigin({ size.x, size.x });
			explosion.setPosition(tankBody.getPosition());
			target.draw(explosion, states);
			explosion.setRadius(size.x/2 * (explodeClock.getElapsedTime().asSeconds() / explodeDuration.asSeconds()));
			explosion.setOrigin({ explosion.getRadius(), explosion.getRadius() });
		}
	}

};
