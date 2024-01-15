#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* window)
{
	currentWindow = window;
	board = new Board(8, 8, window);
}

GameManager::~GameManager()
{
}

void GameManager::onClick(float x, float y)
{
	if (!waitForPromotion)
	{
		if (SelectedPiece != nullptr)
		{
			waitForPromotion = board->MovePiece(&isWhiteTurn, x, y, SelectedPiece);
			board->DeselectPiece(SelectedPiece);
			if (!waitForPromotion)
			{
				SelectedPiece = nullptr;
			}
		}
		if (!waitForPromotion)
		{
			SelectedPiece = board->SelectPiece(isWhiteTurn, x, y);
		}
	}
	else
	{
		waitForPromotion = board->ChoosePromotion(SelectedPiece, x, y, &isWhiteTurn);
		if (!waitForPromotion)
		{
			SelectedPiece = nullptr;
		}
	}
}

void GameManager::Display()
{
	board->Display(SelectedPiece);
	if (waitForPromotion)
	{
		board->DisplayPromotion(SelectedPiece);
	}
}