#include "Text.h"

Text::Text(string text, string font, int size)
{
	if (!myFont.loadFromFile(font))
	{
		sf::err() << "Couldn't load font\n";
	}

	myText = sf::Text(text, myFont, size);
}

void Text::Center(sf::Vector2i element, sf::Vector2u size)
{
	sf::FloatRect textRect = myText.getLocalBounds();
	myText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	myText.setPosition(sf::Vector2f(element.x + (size.x / 2.0f), element.y + (size.y / 2.0f)));
}

void Text::display(sf::RenderWindow* window)
{
	window->draw(myText);
}