#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	title = new Text("Rune Chess", "font/arial.ttf", 32);
	title->Center(sf::Vector2i(0, 0), sf::Vector2u(window->getSize().x, window->getSize().y / 4));
	buttons.push_back(new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 200), "Play"));
	buttons.push_back(new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 300), "Play VS IA"));
	buttons.push_back(new Button(sf::Color::Blue, sf::Vector2u(100, 50), sf::Vector2i(window->getSize().x / 2 - 50, 400), "Quit"));
}

void Menu::Display(sf::RenderWindow* window)
{
	title->display(window);
	for (Button* button : buttons)
	{
		button->Display(window);
	}
}

bool Menu::OnClick(sf::RenderWindow* window, sf::Vector2i pos)
{
	for(int i =0 ;i<buttons.size(); i++)
	{
		if(buttons[i]->OnClick(pos))
		{
			switch(i)
			{
			case 0:
				return false;
			case 1:
				return false;
			case 2:
				window->close();
				return true;
			}
		}
	}
	return true;
}
