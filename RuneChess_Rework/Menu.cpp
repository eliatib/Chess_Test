#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	title = new Text("Rune Chess", "font/arial.ttf", 18);
	title->Center(window->getPosition(), window->getSize());
	play = new Button(sf::Color::Blue, sf::Vector2u(80, 20), sf::Vector2i(400, 900), "Play");
}

void Menu::Display(sf::RenderWindow* window)
{
	title->display(window);
	play->Display(window);
}
