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
	bool move = false;
	bool accessibleOnlyKing = false;
	std::vector<bool> controlled{ false,false };
	std::vector<sf::Vector2i> alowedMoves;

public:
	Cell();
	Cell(sf::RectangleShape rectRef);
	void defineControl(int line, int col, std::vector< std::vector< Cell* > >* boardCells);
	bool verifyCheckMate(int line, int col, std::vector< std::vector< Cell* > >* boardCells);

	void SetPiece(Piece* newPiece);
	void SetRect(sf::RectangleShape newRect);
	void SetMove(bool IsAMove);

	Piece* GetPiece();
	sf::RectangleShape GetRect();
	sf::CircleShape GetCircle();
	bool GetMove();
	std::vector<bool> getControlled();
};
#endif
