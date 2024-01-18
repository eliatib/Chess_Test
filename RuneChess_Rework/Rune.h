#pragma once
#include "Cell.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

class Rune
{
public:
	Rune(sf::Sprite sprite) { runeSprite = sprite; };
	virtual void LauchEffect() {};
	virtual void Verification() {};
	virtual void DisplayRune(sf::RenderWindow* window, sf::Vector2f pos) {};
private:
	 sf::Sprite runeSprite;
};

