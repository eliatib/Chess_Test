#include "Knight.h"
#include "King.h"

void Knight::ShowMove(std::vector<std::vector<Cell*>>* boardCells)
{
	for (int i = -2; i <= 2; i++)
	{
		int y = pos.y + i;
		if (y >= 0 && y < (*boardCells).size())
		{
			int dec = std::abs(i) == 2 ? 1 : std::abs(i) == 1 ? 2 : -1;
			for (int j = -1 * dec; j <= 1 * dec; j = j + (2 * dec))
			{
				int x = pos.x + j;
				if (x >= 0 && x < (*boardCells)[y].size())
				{
					if (x >= 0 && x < (*boardCells)[y].size() && ((*boardCells)[y][x]->GetPiece() == nullptr || (*boardCells)[y][x]->GetPiece()->white != white))
					{
						possibleMoves.push_back(sf::Vector2i(
							x,
							y
						));
					}
				}
			}
		}
	}
}