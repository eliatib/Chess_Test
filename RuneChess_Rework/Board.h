#ifndef BOARD
#define BOARD
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"

class Board
{
public:
	Board() {};
	~Board();
	Board(int width, int height, sf::RenderWindow* window);
	void Display();
	Piece* SelectPiece(bool isWhite, float x, float y);
	void DeselectPiece(Piece* piece);
	void MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece);
private:
	void createBoard(int width, int height);
	void createPieces();
	void SetTexture();
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	std::vector< std::vector< Cell* > > boardCells;
	sf::Texture pieceTexture;
	std::vector < sf::CircleShape > movement;
	std::vector < Piece* > blackPiece;
	std::vector < Piece* > whitePiece; 
	sf::RenderWindow* gameWindow = nullptr;
	sf::Vector2i boardSize;
	float cellSize;
};
#endif

