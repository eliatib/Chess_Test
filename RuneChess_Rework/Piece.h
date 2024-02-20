#ifndef PIECE
#define PIECE
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Piece
{
public:
	/**
	* Creates a Piece
	*
	* @param isWhite if the color of the piece is white
	*/
	Piece();
	/**
	 * Default destructor
	 */
	virtual ~Piece() {};
	virtual void CalculatePossibleMove(std::vector< std::vector< Cell* > > boardCells) {};
	virtual int GetPoint() { return 0; };

	bool white{ true };
	std::vector< sf::Vector2i > possibleMoves;
	sf::Sprite pieceSprite;
	sf::Vector2i pos = sf::Vector2i(0, 0);
	char character;
	bool asMove{ false };
	Cell* currentCell = nullptr;
};
#endif // !PIECE
