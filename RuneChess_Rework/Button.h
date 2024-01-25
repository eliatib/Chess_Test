#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"
class Button
{
public:
	Button() {};
	Button(sf::Color color, sf::Vector2u size, sf::Vector2i pos, string text);
	void OnClick(sf::RenderWindow* window);
	void Hover(sf::RenderWindow* window);
	void Display(sf::RenderWindow* window);
private:
	sf::RectangleShape backgroundRect;
	Text* B_text = nullptr;
};
