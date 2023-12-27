#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Cell.h"
#include "Piece.h"

class GameManager
{
public:
	
	GameManager() : currentWindow(nullptr), isWhiteTurn(true) {};
	GameManager(sf::RenderWindow* window = nullptr);
	~GameManager();
	void onClick(float x, float y);

	void Display();
private:
	bool isWhiteTurn = true;
	bool waitForPromotion = false;
	Piece* SelectedPiece;
	Board* board = nullptr;
	sf::RenderWindow* currentWindow;
	std::vector< std::vector< Cell > > cells;
	std::vector < sf::Sprite > boardPieces;
};

#endif // !GAME_MANAGER