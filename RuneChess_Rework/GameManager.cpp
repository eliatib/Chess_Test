#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* window)
{
	currentWindow = window;
	board = new Board(8, 8, window);
	menu = new Menu(window);
}

GameManager::~GameManager()
{
}

void GameManager::onClick(float x, float y)
{
	if (!waitForPromotion)
	{
		//verifRune ? launchRune
		if (SelectedPiece != nullptr)
		{
			waitForPromotion = board->MovePiece(&isWhiteTurn, x, y, SelectedPiece, checkmate);
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
		waitForPromotion = board->ChoosePromotion(SelectedPiece, x, y, &isWhiteTurn, checkmate);
		if (!waitForPromotion)
		{
			SelectedPiece = nullptr;
		}
	}

	if (checkmate)
	{
		std::cout << "checkmate" << std::endl;
	}
}

void GameManager::Display()
{
	menu->Display(currentWindow);
	/*
	board->Display(SelectedPiece);
	if (waitForPromotion)
	{
		board->DisplayPromotion(SelectedPiece);
	}
	*/
}