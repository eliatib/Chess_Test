#ifndef CELL
#define CELL
#include <SFML/Graphics.hpp>


class Piece;

class Cell
{
private:
	Piece *piece = nullptr;
	sf::RectangleShape rect;
	sf::CircleShape moveCircle;
	bool move = false;

public:
	Cell();
	Cell(sf::RectangleShape rectRef);

	void SetPiece(Piece* newPiece);
	void SetRect(sf::RectangleShape newRect);
	void SetMove(bool IsAMove);

	Piece* GetPiece();
	sf::RectangleShape GetRect();
	sf::CircleShape GetCircle();
	bool GetMove();
};
#endif


