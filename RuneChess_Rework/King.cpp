#include "King.h"
#include <iostream>

void King::CalculatePossibleMove(std::vector<std::vector<Cell>>* boardCells)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int x = pos.x + i;
			int y = pos.y + j;
			if (
				x >= 0 && y >= 0 && y < boardCells->size() && x < (*boardCells)[y].size()
				&& ((*boardCells)[y][x].GetPiece() == nullptr || (*boardCells)[y][x].GetPiece()->white != white)
				)
			{
				possibleMoves.push_back(sf::Vector2i(
					x,
					y)
				);
			}
		}
	}

	// roc
	if (!asMove)
	{
		for (int right = -1; right < 2; right += 2)
		{
			for (int i = 1; pos.x + (i * right) >= 0 && pos.x + (i * right) < (*boardCells)[pos.y].size(); i++)
			{
				int x = pos.x + (i * right);
				int y = pos.y;
				Piece* piece = (*boardCells)[y][x].GetPiece();
				if (piece == nullptr)
				{
					continue;
				}
				else if (piece->white == white && typeid(*piece) == typeid(Rook) && !piece->asMove)
				{
					possibleMoves.push_back(sf::Vector2i(
						x,
						y)
					);
				}
				break;
			}
		}
	}
}

int King::GetPoint()
{
	return 100;
}
