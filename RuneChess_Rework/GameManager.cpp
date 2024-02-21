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
	else if(checkmate)
	{
		if(comeBackMenu->OnClick(pos))
		{
			inMenu = true;
			checkmate = false;
			board = new Board(8, 8, currentWindow);
			isWhiteTurn = true;
		}
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
			EndGame();
		}
	}
}

void GameManager::Display()
{
	if (inMenu)
	{
		menu->Display(currentWindow);
	}
	else if(checkmate)
	{
		currentWindow->draw(endBG);
		winner->display(currentWindow);
		comeBackMenu->Display(currentWindow);
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

void GameManager::EndGame()
{
	endBG.setPosition(0, 0);
	endBG.setSize(sf::Vector2f(currentWindow->getSize().x, currentWindow->getSize().y));
	endBG.setFillColor(sf::Color(0, 0, 0, 200));

	winText = isWhiteTurn ? "White" : "Black";
	winText += " Win";
	winner = new Text(winText, "font/arial.ttf", 16);
	winner->Center(sf::Vector2i(endBG.getPosition().x, endBG.getPosition().y), sf::Vector2u(endBG.getSize().x, (endBG.getSize().y / 3) * 2));

	comeBackMenu = new Button(sf::Color::Blue, sf::Vector2u(150, 50), sf::Vector2i(currentWindow->getSize().x / 2 - 75, currentWindow->getSize().y / 2 - 75), "Go Back To Menu");
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

	if(checkmate)
	{
		EndGame();
	}
	//board->writeBoard();
}
