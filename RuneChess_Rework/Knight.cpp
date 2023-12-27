#include "Knight.h"

void Knight::ShowMove(std::vector<std::vector<Cell*>>* boardCells)
{
	for (int i = -2; i <= 2; i++)
	{
		if (std::abs(i) == 2 && pos.y + i >= 0 && pos.y + i < (*boardCells).size())
		{
			for (int y = -1; y <= 1; y = y + 2)
			{
				if (pos.x + y >= 0 && pos.x + y < (*boardCells)[pos.y + i].size() && ((*boardCells)[pos.y + i][pos.x + y]->GetPiece() == nullptr || (*boardCells)[pos.y + i][pos.x + y]->GetPiece()->white != white))
				{
					possibleMove.push_back(sf::Vector2i(
						pos.x + y,
						pos.y + i
					));
				}
			}
		}
		else if (std::abs(i) == 1 && pos.y + i >= 0 && pos.y + i < (*boardCells).size())
		{
			for (int y = -2; y <= 2; y = y + 4)
			{
				if (pos.x + y >= 0 && pos.x + y < (*boardCells)[pos.y + i].size() && ((*boardCells)[pos.y + i][pos.x + y]->GetPiece() == nullptr || (*boardCells)[pos.y + i][pos.x + y]->GetPiece()->white != white))
				{
					possibleMove.push_back(sf::Vector2i(
						pos.x + y,
						pos.y + i
					));
				}
			}
		}
	}
}
