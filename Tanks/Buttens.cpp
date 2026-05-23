#include <SFML/Graphics.hpp>

class Buttens : public sf::Drawable {
private:
	sf::RectangleShape Butten_Block;
	sf::Font font;
	const char* text;
	int size= 0 ;


public:

	Buttens() {
		Butten_Block.setSize({ 200, 50 });
		Butten_Block.setPosition({ 300, 200 });
		font.openFromFile("C:/Windows/Fonts/Arial.ttf");
		text = "defoult";

	}

	Buttens(sf::Vector2f size, sf::Vector2f coordinate, char* text, sf::Font font, sf::Color color) {
		Butten_Block.setSize(size);
		Butten_Block.setPosition(coordinate);
		Butten_Block.setFillColor(color);
		this->font = font;
		this->text = text;
		while (text[this->size] != '\0') {
			this->size++;
		}
		this->size = this->size <= 4 ? 5 : this->size;
	}

	bool click(sf::Vector2f coordinate, bool isClick) {
		if (coordinate.x >= Butten_Block.getPosition().x && coordinate.x <= Butten_Block.getPosition().x + Butten_Block.getSize().x &&
			coordinate.y >= Butten_Block.getPosition().y && coordinate.y <= Butten_Block.getPosition().y +  Butten_Block.getSize().y && isClick )
			return true;
		return false;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(Butten_Block, states);
		sf::Text Text(font, text, Butten_Block.getSize().y / 1.5);
		Text.setPosition({ Butten_Block.getPosition().x + Butten_Block.getSize().x/size, Butten_Block.getPosition().y});
		Text.setFillColor(sf::Color::Black);
		target.draw(Text, states);
	}

};
