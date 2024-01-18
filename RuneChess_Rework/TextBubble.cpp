#include "TextBubble.h"

TextBubble::TextBubble(std::string text, sf::Vector2f size, sf::Color color)
{
	bubbleSize = size;
	bubbleText = text;
	backgroundColor = color;
}

void TextBubble::DrawBubble(sf::RenderWindow* window, sf::Vector2f pos)
{

}

