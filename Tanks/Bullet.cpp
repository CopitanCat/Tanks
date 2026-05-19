#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
private:
	sf::CircleShape bulletBody;
	sf::Vector2f coordinates = {-1,-1};
	sf::Angle anglex, angley;
	float radius = 5;
	bool alive = false;
	int bound_Count = 5;

public:
	// Constructors
	Bullet() {
		bulletBody.setPosition(coordinates);
		bulletBody.setRadius(radius);
		bulletBody.setFillColor(sf::Color::Red);
		bulletBody.setOrigin({ radius, radius });
		alive = true;
	}
	Bullet(sf::Vector2f coordinates) {
		this->coordinates = coordinates;
		bulletBody.setPosition(coordinates);
		bulletBody.setRadius(radius);
		bulletBody.setFillColor(sf::Color::Red);
		bulletBody.setOrigin({ radius, radius });
		alive = true;
	}
	Bullet(float radius) {
		this->radius = radius;
		alive = true;
		bulletBody.setPosition(coordinates);
		bulletBody.setRadius(radius);
		bulletBody.setFillColor(sf::Color::Red);
		bulletBody.setOrigin({ radius, radius });
	}
	Bullet(sf::Vector2f coordinates, float radius) {
		this->coordinates = coordinates;
		alive = true;
		this->radius = radius;
		bulletBody.setPosition(coordinates);
		bulletBody.setRadius(radius);
		bulletBody.setFillColor(sf::Color::Red);
		bulletBody.setOrigin({ radius, radius });
	}


	// Setters

	void setAngle(sf::Angle angle) {
		anglex = angle;
		angley = angle;
	}

	// Getters

	sf::Vector2f getPosition() {
		return bulletBody.getPosition();
	}

	bool isAlive() {
		return alive;
	}

	int getBoundCount() {
		return bound_Count;
	}

	// Actions

	void move(float speed, bool isTouch) {
		if (isTouch) {
			if (bound_Count > 0) {
				anglex = -anglex;
				angley = -angley;
				bound_Count--;
			}
			else
				alive = false;
		}
		bulletBody.move({ speed * std::cos(anglex.asRadians()), speed * std::sin(angley.asRadians()) });
		if (bound_Count <= 0) {
			alive = false;
		}
	}

	void setAlive(bool Alive) {
		this->alive = Alive;
	}


	// Collision 

	bool checkCollision(const sf::Shape& shape) {
		return bulletBody.getGlobalBounds().findIntersection(shape.getGlobalBounds()).has_value();
	}



	// Draw
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		if (alive)
			target.draw(bulletBody, states);
	}
};
