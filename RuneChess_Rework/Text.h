#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
class Text
{
public:
	Text() {};
	Text(string text, string font, int size);
	void Center(sf::Vector2i element, sf::Vector2u size);
	void SetPos(sf::Vector2f pos);
	void display(sf::RenderWindow* window);
private:
	sf::Text myText;
	sf::Font myFont;
};
