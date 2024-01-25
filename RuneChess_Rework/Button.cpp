#include "Button.h"

Button::Button(sf::Color color, sf::Vector2u size, sf::Vector2i pos, string text)
{
	backgroundRect.setFillColor(color);
	backgroundRect.setPosition(sf::Vector2f(pos.x, pos.y));
	backgroundRect.setSize(sf::Vector2f(size.x, size.y));
	B_text = new Text(text, "font/arial.ttf", 16);
	B_text->Center(sf::Vector2i(backgroundRect.getPosition().x, backgroundRect.getPosition().y), sf::Vector2u(backgroundRect.getSize().x, backgroundRect.getSize().y));
}

bool Button::OnClick(sf::Vector2i pos)
{
	if (backgroundRect.getPosition().x <  pos.x && backgroundRect.getPosition().x + backgroundRect.getSize().x > pos.x 
		&& backgroundRect.getPosition().y <  pos.y && backgroundRect.getPosition().y + backgroundRect.getSize().y > pos.y)
	{
		return true;
	}
	return false;
}

void Button::Hover(sf::RenderWindow* window)
{
}

void Button::Display(sf::RenderWindow* window)
{
	window->draw(backgroundRect);
	B_text->display(window);
}