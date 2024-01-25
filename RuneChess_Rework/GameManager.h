#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include "Menu.h"

class GameManager
{
public:
	
	GameManager() : currentWindow(nullptr), isWhiteTurn(true) {};
	GameManager(sf::RenderWindow* window = nullptr);
	~GameManager();
	void onClick(sf::Vector2i pos);

	void Display();
private:
	bool isWhiteTurn = true;
	bool waitForPromotion = false;
	bool inMenu = true;
	Piece* SelectedPiece;
	Board* board = nullptr;
	Menu* menu = nullptr;
	bool checkmate = false;
	sf::RenderWindow* currentWindow;
	std::vector< std::vector< Cell > > cells;
	std::vector < sf::Sprite > boardPieces;
};

#endif // !GAME_MANAGER