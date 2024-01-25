#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	title = new Text("Rune Chess", "font/arial.ttf", 32);
	title->Center(sf::Vector2i(0, 0), sf::Vector2u(window->getSize().x, window->getSize().y / 4));
	play = new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 200), "Play");
	play_IA = new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 300), "Play VS IA");
	quit = new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 400), "Quit");
}

void Menu::Display(sf::RenderWindow* window)
{
	title->display(window);
	play->Display(window);
	play_IA->Display(window);
	quit->Display(window);
}