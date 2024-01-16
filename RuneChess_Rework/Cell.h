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
	bool showMove = false;

public:
	Cell();
	Cell(sf::RectangleShape rectRef);
	void defineControl(int line, int col, std::vector< std::vector< Cell* > >* boardCells);
	bool verifyCheckMate(int line, int col, std::vector< std::vector< Cell* > >* boardCells);

	bool GetShowMove();
	void SetPiece(Piece* newPiece);
	void SetRect(sf::RectangleShape newRect);
	void SetShowMove(bool showingMove);
	
	
	Piece* GetPiece();
	sf::RectangleShape GetRect();
	sf::CircleShape GetCircle();
	
};
#endif
