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
	Board(int width, int height, sf::RenderWindow* window);

	void Display(Piece* SelectedPiece);
	void writeBoard();
	void DisplayPromotion(Piece* SelectedPiece);
	bool ChoosePromotion(Piece* SelectedPiece, float x, float y, bool* isWhite, bool& checkmate);
	Piece* SelectPiece(bool isWhite, float x, float y);
	void DeselectPiece(Piece* piece);
	bool MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece, bool& checkmate, bool& waitForPromotion);
	void MovePieceIA(bool* isWhite, sf::Vector2i piecePos, sf::Vector2i move, bool& checkmate);
	std::vector< std::vector< Cell* > > GetBoard();
	std::vector< Piece* > GetPieces();
	void CreateTexturePiece(Piece* piece);
	void InitializeMoves();

private:
	void createBoard(int width, int height);
	void createPieces();
	void SetTexture();
	void CreateSpritePromotion(Piece* selectedPiece);
	bool VerifyKingNotinCheck(Piece* king, sf::Vector2i kingPos, sf::Vector2i pos, sf::Vector2i move);
	bool VerifyAllMove(Piece* king);
	
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	Piece* inCheckPiece;
	std::vector< Piece* > kingsPiece;
	std::vector< Piece* > pieces;
	std::vector< std::vector< Cell* > > boardCells;
	sf::Texture pieceTexture;
	sf::Texture RuneTexture;
	std::vector<sf::Sprite> SpritePromotion;
	std::vector < sf::CircleShape > movement;
	sf::RenderWindow* gameWindow = nullptr;
	sf::Vector2f boardSize;
	sf::Vector2f pieceSize;
	sf::Vector2f scale;
	float cellSize;
};
#endif
