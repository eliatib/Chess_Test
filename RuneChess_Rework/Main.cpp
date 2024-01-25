#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1900, 800), "Rune Chess", sf::Style::Titlebar | sf::Style::Close);
	GameManager* gm = new GameManager(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "click" << std::endl;
					gm->onClick(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
			}
		}

		window.clear(sf::Color(204, 204, 255));
		gm->Display();
		window.display();
	}

	return 0;
}