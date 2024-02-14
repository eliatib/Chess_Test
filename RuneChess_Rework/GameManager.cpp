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
		if (!waitForPromotion && !hasPlay)
		{
			//verifRune ? launchRune
			if (SelectedPiece != nullptr)
			{
				hasPlay = board->MovePiece(&isWhiteTurn, pos.x, pos.y, SelectedPiece, checkmate, waitForPromotion);
				board->DeselectPiece(SelectedPiece);
				if (!waitForPromotion)
				{
					SelectedPiece = nullptr;
				}
				
			}
			if (!waitForPromotion && !hasPlay)
			{
				SelectedPiece = board->SelectPiece(isWhiteTurn, pos.x, pos.y);
			}
		}
		else if(waitForPromotion && hasPlay)
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
		if (waitForPromotion)
		{
			board->DisplayPromotion(SelectedPiece);
		}
	}
}

void GameManager::changeTurn()
{
	if (!hasPlay && !waitForPromotion && againstIA && !isWhiteTurn)
	{
		playIA();
	}
	else if(!waitForPromotion && hasPlay)
	{
		isWhiteTurn = !isWhiteTurn;
		hasPlay = false;
	}
}

void GameManager::playIA()
{
	//board->writeBoard();
	std::vector <sf::Vector2i> move = ia->Play(currentWindow, *board, checkmate);
	board->MovePieceIA(&isWhiteTurn, move[0], move[1], checkmate);
	hasPlay = true;
	if (SelectedPiece != nullptr)
	{
	board->DeselectPiece(SelectedPiece);
	SelectedPiece = nullptr;
	}
	board->InitializeMoves();
	//board->writeBoard();
}
