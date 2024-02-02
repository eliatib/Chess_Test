#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* window)
{
	currentWindow = window;
	board = new Board(8, 8, window);
	menu = new Menu(window);
	ia = new IA();
}

GameManager::~GameManager()
{
}

void GameManager::onClick(sf::Vector2i pos)
{
	if (inMenu)
	{
		inMenu = menu->OnClick(currentWindow, pos, &againstIA);
	}
	else if ((againstIA && isWhiteTurn) || !againstIA)
	{
		if (!waitForPromotion)
		{
			//verifRune ? launchRune
			if (SelectedPiece != nullptr)
			{
				waitForPromotion = board->MovePiece(&isWhiteTurn, pos.x, pos.y, SelectedPiece, checkmate);
				board->DeselectPiece(SelectedPiece);
				if (!waitForPromotion)
				{
					SelectedPiece = nullptr;
				}
			}
			if (!waitForPromotion)
			{
				SelectedPiece = board->SelectPiece(isWhiteTurn, pos.x, pos.y);
			}
		}
		else
		{
			waitForPromotion = board->ChoosePromotion(SelectedPiece, pos.x, pos.y, &isWhiteTurn, checkmate);
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
}

void GameManager::Display()
{
	if (inMenu)
	{
		menu->Display(currentWindow);
	}
	else
	{
		board->Display(SelectedPiece);
		if (againstIA && !isWhiteTurn && !iaIsPlaying)
		{
			iaIsPlaying = true;
			std::cout << "here" << std::endl;
			ia->Play(currentWindow, board, &isWhiteTurn, checkmate);
			iaIsPlaying = false;
			isWhiteTurn = true;
		}
		if (waitForPromotion)
		{
			board->DisplayPromotion(SelectedPiece);
		}
	}
}