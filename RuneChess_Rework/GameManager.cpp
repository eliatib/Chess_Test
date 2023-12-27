#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* window)
{
	currentWindow = window;
	board = new Board(8,8, window);	
}

GameManager::~GameManager()
{
}

void GameManager::onClick(float x, float y)
{
	if(!waitForPromotion)
	{
		if (SelectedPiece != nullptr)
		{
			board->MovePiece(&isWhiteTurn, x, y, SelectedPiece);
			board->DeselectPiece(SelectedPiece);
		}
		SelectedPiece = board->SelectPiece(isWhiteTurn,x,y);
	}
	else
	{
	
	}
}

void GameManager::Display()
{
	board->Display();
}
