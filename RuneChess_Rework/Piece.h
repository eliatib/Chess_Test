#ifndef PIECE
#define PIECE
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Piece
{
public :
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
    virtual void ShowMove(std::vector< std::vector< Cell* > >* boardCells) {};

    bool white{ true };
    std::vector< sf::Vector2i > possibleMove;
    sf::Sprite pieceSprite;
    sf::Vector2i pos = sf::Vector2i(0, 0);
    bool asMove{ false };
    Cell* currentCell = nullptr;
};
#endif // !PIECE


