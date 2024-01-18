#pragma once
#include "Rune.h"

class SacrificialPawn : public Rune
{
	void LauchEffect() ;
	void Verification() ;
	void DisplayRune(sf::RenderWindow* window, sf::Vector2f pos) ;
};

