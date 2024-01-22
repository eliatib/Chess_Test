#include "Button.h"

Button::Button(sf::Color color, sf::Vector2u size, sf::Vector2i pos, string text)
{
	backgroundRect.setFillColor(color);
	backgroundRect.setPosition(sf::Vector2f(pos.x,pos.y));
	backgroundRect.setSize(sf::Vector2f(size.x, size.y));
	B_text = new Text("text","font",16);
}

void Button::OnClick(sf::RenderWindow* window)
{
}

void Button::Hover(sf::RenderWindow* window)
{
}

void Button::Display(sf::RenderWindow* window)
{
	window->draw(backgroundRect);
	B_text->display(window);
}
