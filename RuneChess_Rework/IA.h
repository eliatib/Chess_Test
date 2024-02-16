#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class IA
{
public:
	std::vector <sf::Vector2i> Play(sf::RenderWindow* window, Board board, bool& checkmate);
private:
	sf::Vector2i bestMove;
	sf::Vector2i piecePos;
	int ite = 2;
	void ChooseMove(Board board);
	int MiniMax(std::vector<std::vector<Cell*>> cells, int iteration, bool isWhite);
	void writeBoard(std::vector<std::vector<Cell*>> cells);
	void recreatePiece( std::vector<std::vector<Cell*>>* cells, char c, sf::Vector2i pos, bool isWhite, bool asMove);
	int countPoint(std::vector<std::vector<Cell*>> cells);
	void TestMove(std::vector<std::vector<Cell*>>* cells, Piece* piece, sf::Vector2i move);
};
