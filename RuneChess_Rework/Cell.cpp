#include "Cell.h"

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
	move = false;
}

void Cell::SetPiece(Piece* newPiece)
{
	piece = newPiece;
}

void Cell::SetRect(sf::RectangleShape newRect)
{
	rect = newRect;
}

void Cell::SetMove(bool IsAMove)
{
	move = IsAMove;
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

bool Cell::GetMove()
{
	return move;
}
