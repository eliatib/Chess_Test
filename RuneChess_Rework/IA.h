#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class IA
{
public:
	void Play(sf::RenderWindow* window, Board* board, bool* isWhite, bool &checkmate);
private :
	sf::Vector2i bestMove;
	Piece* pieceToMove;
	void ChooseMove(Board* board);
	int MiniMax(Board * board,std::vector<std::vector<Cell>> cells, std::vector<Piece*> pieces, int iteration, bool isWhite);
	int countPoint(std::vector<std::vector<Cell>> cells);
	void TestMove(std::vector<std::vector<Cell>>* cells, Piece* piece, sf::Vector2i move);
};

