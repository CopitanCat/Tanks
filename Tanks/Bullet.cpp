#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
private:
	sf::CircleShape bulletBody;
	sf::Vector2f coordinates = {-1,-1};
	sf::Angle angle;
	float radius = 5;
	bool alive = false;
	int bound_Count = 3;
	sf::Vector2f size;

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
		this->angle = angle;
	}

	void setAlive(bool Alive) {
		this->alive = Alive;
	}

	void setSize(sf::Vector2f size) {
		this->size = size;
	}
	// Getters

	sf::Vector2f getPosition() {
		coordinates = bulletBody.getPosition();
		return coordinates;
	}

	float getRadius() {
		return radius;
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

				float vx = std::cos(angle.asRadians());
				float vy = std::sin(angle.asRadians()); // was angley — now anglex

				if (size.x >= size.y)
					vy = -vy;  // horizontal wall: flip Y
				else
					vx = -vx;  // vertical wall: flip X
				angle = sf::radians(std::atan2(vy, vx));
				bound_Count--;
			}
			else {
				alive = false;
			}
		}
		bulletBody.move({
			speed * std::cos(angle.asRadians()),
			speed * std::sin(angle.asRadians()) // was angley
			});
	}


	// Collision 

	bool checkCollision(sf::Shape* shape) {
		if (bulletBody.getGlobalBounds().findIntersection(shape->getGlobalBounds())) {
			return true;
		}
		return false;
	}


	// Draw
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		if (alive)
			target.draw(bulletBody, states);
	}
};
