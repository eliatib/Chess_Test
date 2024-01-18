#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextBubble
{
public:
	TextBubble(std::string text, sf::Vector2f size, sf::Color color);
	void DrawBubble(sf::RenderWindow* window, sf::Vector2f pos);
private:
	std::string bubbleText;
	sf::Vector2f bubbleSize;
	sf::Color backgroundColor;
};

