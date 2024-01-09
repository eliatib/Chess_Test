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
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

class Board
{
public:
	Board() {};
	~Board();
	Board(int width, int height, sf::RenderWindow* window)
	{
		gameWindow = window;
		createBoard(width, height);
		createPieces();
		verifyBoardControl();
	}
	void Display();
	void DisplayPromotion(Piece* SelectedPiece);
	bool ChoosePromotion(Piece* SelectedPiece, float x, float y, bool* isWhite);
	Piece* SelectPiece(bool isWhite, float x, float y);
	void DeselectPiece(Piece* piece);
	bool MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece);
private:
	void createBoard(int width, int height);
	void createPieces();
	void SetTexture();
	void CreateSpritePromotion(Piece* selectedPiece);
	void verifyBoardControl();
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	Piece* inCheckPiece;
	std::vector< Piece* > kingsPiece;
	std::vector< std::vector< Cell* > > boardCells;
	sf::Texture pieceTexture;
	std::vector<sf::Sprite> SpritePromotion;
	std::vector < sf::CircleShape > movement;
	sf::RenderWindow* gameWindow = nullptr;
	sf::Vector2i boardSize;
	float cellSize;
};
#endif

