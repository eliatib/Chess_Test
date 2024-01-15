#ifndef CELL
#define CELL
#include <SFML/Graphics.hpp>

class Piece;

class Cell
{
private:
	Piece* piece = nullptr;
	sf::RectangleShape rect;
	sf::CircleShape moveCircle;

public:
	Cell();
	Cell(sf::RectangleShape rectRef);
	void defineControl(int line, int col, std::vector< std::vector< Cell* > >* boardCells);
	bool verifyCheckMate(int line, int col, std::vector< std::vector< Cell* > >* boardCells);

	void SetPiece(Piece* newPiece);
	void SetRect(sf::RectangleShape newRect);

	Piece* GetPiece();
	sf::RectangleShape GetRect();
	sf::CircleShape GetCircle();
};
#endif
