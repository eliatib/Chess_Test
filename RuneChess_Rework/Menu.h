#pragma once
#include "Text.h";
#include "Button.h";
class Menu
{
public:
	Menu(sf::RenderWindow* window);
	void Display(sf::RenderWindow* window);
private:
	Text* title = nullptr;
	Button* play = nullptr;
	Button* play_IA = nullptr;
	Button* quit = nullptr;
};

