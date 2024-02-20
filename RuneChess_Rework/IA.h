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
	int ite = 3;
	void ChooseMove(Board board);
	std::vector<std::vector<Cell*>> MakeBoardCopy(std::vector<std::vector<Cell*>> cellsToCopy);
	int MiniMax(std::vector<std::vector<Cell*>> cells,int alpha,int beta, int iteration, bool isWhite);
	void writeBoard(std::vector<std::vector<Cell*>> cells);
	int countPoint(std::vector<std::vector<Cell*>> cells);
	void TestMove(std::vector<std::vector<Cell*>>* cells, Piece* piece, sf::Vector2i move);
};
