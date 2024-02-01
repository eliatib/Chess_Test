#pragma once
#include "Text.h";
#include "Button.h";
class Menu
{
public:
	Menu(sf::RenderWindow* window);
	void Display(sf::RenderWindow* window);
	bool OnClick(sf::RenderWindow* window, sf::Vector2i pos, bool* ia);
private:
	Text* title = nullptr;
	std::vector<Button*> buttons;
};

