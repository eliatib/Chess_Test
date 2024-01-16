#include "Cell.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Cell::Cell()
{
}

Cell::Cell(sf::RectangleShape rectRef)
{
	rect = rectRef;
	sf::CircleShape circle(16);
	circle.setFillColor(sf::Color(255, 255, 255, 200));
	circle.setPosition(
		rect.getPosition().x + (rect.getSize().x / 2) - 16,
		rect.getPosition().y + (rect.getSize().y / 2) - 16
	);
	moveCircle = circle;
	piece = nullptr;
}

void Cell::SetPiece(Piece* newPiece)
{
	piece = newPiece;
}

void Cell::SetRect(sf::RectangleShape newRect)
{
	rect = newRect;
}

bool Cell::GetShowMove()
{
	return showMove;
}

void Cell::SetShowMove(bool showingMove)
{
	showMove = showingMove;
}

Piece* Cell::GetPiece()
{
	return piece;
}

sf::RectangleShape Cell::GetRect()
{
	return rect;
}

sf::CircleShape Cell::GetCircle()
{
	return moveCircle;
}