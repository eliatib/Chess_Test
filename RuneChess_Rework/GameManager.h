


#ifndef GAME_MANAGER
#define GAME_MANAGER
#define NOMINMAX
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include "Menu.h"
#include "IA.h"

class GameManager
{
public:
	
	GameManager() : currentWindow(nullptr), isWhiteTurn(true) {};
	GameManager(sf::RenderWindow* window = nullptr);
	~GameManager();
	void onClick(sf::Vector2i pos);
	void changeTurn();
	void Display();
private:
	bool isWhiteTurn = true;
	bool hasPlay = false;
	bool iaPlaying = false;
	bool waitForPromotion = false;
	bool inMenu = true;
	bool againstIA = false;
	Piece* SelectedPiece;
	Board* board = nullptr;
	Menu* menu = nullptr;
	IA* ia = nullptr;
	bool checkmate = false;
	sf::RenderWindow* currentWindow;
	std::vector< std::vector< Cell > > cells;
	std::vector < sf::Sprite > boardPieces;
};

#endif // !GAME_MANAGER