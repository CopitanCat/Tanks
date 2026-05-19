#include <SFML/Graphics.hpp>
#include "Bullet.cpp"

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

	// getters

	std::vector<Bullet>& getBullets() {
		return bullets;
	}

	int getBulletCount() {
		return bulletCount;
	}


	// Actions
	void move(float speed) {
		if (tankBody.getPosition().x+10 <size.y/2 || tankBody.getPosition().x + 10 > size_OF_window.x || tankBody.getPosition().y + 10 < size.y/2 || tankBody.getPosition().y + 10 > size_OF_window.y-size.y/2) {
			tankBody.move({ -abs(speed) * 2.7f *(std::cos(angle.asRadians())), -abs(speed) * 2.7f * (std::sin(angle.asRadians())) });
		}
		else
			tankBody.move({speed* std::cos(angle.asRadians()), speed * std::sin(angle.asRadians())});
	}

	void rotate(float angle) {
		tankBody.rotate(sf::degrees(angle));
		this->angle += sf::degrees(angle);
	}

	void shoot() {
		coordinates = tankBody.getPosition();
		if (bulletCount > 0) {
			bullets.push_back(Bullet({coordinates.x + cos(angle.asRadians())*(size.x/1.5f), coordinates.y + sin(angle.asRadians())*(size.y/1.5f)}));
			bullets.back().setAngle(angle);
			bulletCount--;
		}
	
	}

	void updateBullets(float speed,const sf::Shape& shape) {
		for (auto& bullet : bullets) {
			bullet.move(speed * 1.3, BulletBoundColision(bullet, shape));
			if (bullet.getPosition().x < 0 || bullet.getPosition().x > size_OF_window.x ||
				bullet.getPosition().y < 0 || bullet.getPosition().y > size_OF_window.y) {
			}
			if (bullet.getBoundCount() <= 0) {
				bullet.setAlive(false);
			}
		}
		removeDeadBullets();
	}



	void reload() {
		bulletCount = 5;
	}


	// Collision Detection
	bool collisionOFtank(sf::Vector2f coordinate, sf::Vector2f size) {
		if (tankBody.getPosition().x  <= size.x || tankBody.getPosition().x  >= coordinate.x || tankBody.getPosition().y + this->size.y / 2 >= coordinate.y || tankBody.getPosition().y + this->size.y / 2 <= size.y)
			return true;
		else return false;
	}


	void collisionWithBullet(const sf::Shape& shape) {
	}

	bool BulletBoundColision(Bullet bullet, const sf::Shape& shape) {
		if (shape.getGlobalBounds().size == size_OF_window) {
			if (bullet.checkCollision(shape) || bullet.getPosition().x>size_OF_window.x || bullet.getPosition().x < 0) {
				return !true;
			}
			else return !false;

		}
		if (bullet.checkCollision(shape)) {
			return true;
		}
		else return false;
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
