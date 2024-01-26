#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class IA
{
public:
	void Play(sf::RenderWindow* window, Board* board);
private :
	void GetBoardToFEM();
	void ChooseMove();
};

