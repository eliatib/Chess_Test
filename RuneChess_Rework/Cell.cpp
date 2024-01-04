#include "Cell.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Cell::Cell()
{
}

Cell::Cell(sf::RectangleShape rectRef)
{
	rect = rectRef;
	sf::CircleShape circle(16);
	circle.setFillColor(sf::Color(255, 255, 255, 200));
	circle.setPosition(
		rect.getPosition().x + (rect.getSize().x / 2) - 16,
		rect.getPosition().y + (rect.getSize().y / 2) - 16
	);
	moveCircle = circle;
	piece = nullptr;
	move = false;
}

void Cell::defineControl(int line, int col, std::vector< std::vector< Cell* > >* boardCells)
{
	controlled[0] = false;
	controlled[1] = false;
	//R,Q,K
	for (int right = -1; right < 2; right++)
	{
		for (int down = -1; down < 2; down++)
		{
			if ((right != 0 || down != 0) && (right == 0 || down == 0))
			{
				for (int i = 1;
					line + (i * down) >= 0 && line + (i * down) < boardCells->size() && col + (i * right) >= 0 && col + (i * right) < (*boardCells)[line + (i * down)].size();
					i++)
				{
					int y = line + (i * down);
					int x = col + (i * right);
					Piece* piece = (*boardCells)[y][x]->GetPiece();
					if (piece == nullptr)
					{
						continue;
					}
					else if (typeid(*piece) == typeid(Rook) || typeid(*piece) == typeid(Queen) || (i == 1 && typeid(*piece) == typeid(King)))
					{
						controlled[piece->white ? 0 : 1] = true;
					}
					break;
				}
			}
		}
	}
	//K,P,B,Q
	for (int right = -1; right < 2; right += 2)
	{
		for (int down = -1; down < 2; down += 2)
		{
			for (
				int i = 1;
				line + (i * down) >= 0 && line + (i * down) < boardCells->size() && col + (i * right) >= 0 && col + (i * right) < (*boardCells)[line + (i * down)].size();
				i++
				)
			{
				int x = col + (i * right);
				int y = line + (i * down);
				Piece* piece = (*boardCells)[y][x]->GetPiece();
				if (piece == nullptr)
				{
					continue;
				}
				else if (typeid(*piece) == typeid(Bishop) || typeid(*piece) == typeid(Queen) || (i == 1 && (typeid(*piece) == typeid(King) || typeid(*piece) == typeid(Pawn))))
				{
					controlled[piece->white ? 0 : 1] = true;
				}
				break;
			}

		}
	}
	//N
	for (int i = -2; i <= 2; i++)
	{
		int y = line + i;
		if (y >= 0 && y < (*boardCells).size())
		{
			int dec = std::abs(i) == 2 ? 1 : std::abs(i) == 1 ? 2 : -1;
			
			for (int j = -1*dec; j <= 1 * dec; j = j + (2 * dec))
			{
				int x = col + j;

				if (x >= 0 && x < (*boardCells)[y].size())
				{
					Piece* piece = (*boardCells)[y][x]->GetPiece();
					if (piece == nullptr)
					{
						continue;
					}
					else if (typeid(*piece) == typeid(Knight))
					{
						controlled[piece->white ? 0 : 1] = true;
					}
					break;
				}
			}
		}
	}
}

void Cell::SetPiece(Piece* newPiece)
{
	piece = newPiece;
}

void Cell::SetRect(sf::RectangleShape newRect)
{
	rect = newRect;
}

void Cell::SetMove(bool IsAMove)
{
	move = IsAMove;
}

Piece* Cell::GetPiece()
{
	return piece;
}

sf::RectangleShape Cell::GetRect()
{
	return rect;
}

sf::CircleShape Cell::GetCircle()
{
	return moveCircle;
}

bool Cell::GetMove()
{
	return move;
}

std::vector<bool> Cell::getControlled()
{
	return controlled;
}

