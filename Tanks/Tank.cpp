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
	bool isAlive = true;
	std::unordered_map<sf::Shape*, sf::Vector2f> Map;

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

	// getters

	std::vector<Bullet>& getBullets() {
		return bullets;
	}

	int getBulletCount() {
		return bulletCount;
	}


	// Actions
	void move(float speed) {
		if (checkCollision()) {
			tankBody.move({ speed * 2.7f *(std::cos((sf::degrees(180)-angle).asRadians())), speed * 2.7f * (std::sin(-angle.asRadians())) });
		}
		else
			tankBody.move({speed* std::cos(angle.asRadians()), speed * std::sin(angle.asRadians())});
	}

	void rotate(float angle) {
		tankBody.rotate(sf::degrees(angle));
		this->angle += sf::degrees(angle);
		std::cout << tankBody.getRotation().asDegrees() << std::endl;
	}

	void shoot() {
		coordinates = tankBody.getPosition();
		if (bulletCount > 0) {
			bullets.push_back(Bullet({coordinates.x + cos(angle.asRadians())*(size.x/1.5f), coordinates.y + sin(angle.asRadians())*(size.y/1.5f)}));
			bullets.back().setAngle(angle);
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


	void collisionWithBullet() {

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
		target.draw(tankBody, states);
	}

};
