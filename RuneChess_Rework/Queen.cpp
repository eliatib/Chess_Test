#include "Queen.h"

void Queen::ShowMove(std::vector<std::vector<Cell*>>* boardCells)
{
	//Rook moves
	for (int right = -1; right < 2; right++)
	{
		for (int down = -1; down < 2; down++)
		{
			if ((right != 0 || down != 0) && (right == 0 || down == 0))
			{
				for (int i = 1;
					pos.y + (i * down) >= 0 && pos.y + (i * down) < boardCells->size() && pos.x + (i * right) >= 0 && pos.x + (i * right) < (*boardCells)[pos.y + (i * down)].size();
					i++)
				{
					int x = pos.x + (i * right);
					int y = pos.y + (i * down);
					if ((*boardCells)[y][x]->GetPiece() == nullptr || (*boardCells)[y][x]->GetPiece()->white != white)
					{
						possibleMove.push_back(sf::Vector2i(
							x,
							y)
						);
						if ((*boardCells)[y][x]->GetPiece() != nullptr)
						{
							break;
						}
						continue;
					}
					break;
				}
			}
		}
	}
	//Bishop Move
	for (int right = -1; right < 2; right += 2)
	{
		for (int down = -1; down < 2; down += 2)
		{
			for (
				int i = 1;
				pos.y + (i * down) >= 0 && pos.y + (i * down) < boardCells->size() && pos.x + (i * right) >= 0 && pos.x + (i * right) < (*boardCells)[pos.y + (i * down)].size();
				i++
				)
			{
				int x = pos.x + (i * right);
				int y = pos.y + (i * down);
				if ((*boardCells)[y][x]->GetPiece() == nullptr || (*boardCells)[y][x]->GetPiece()->white != white)
				{
					possibleMove.push_back(sf::Vector2i(
						x,
						y)
					);
					if ((*boardCells)[y][x]->GetPiece() != nullptr)
					{
						break;
					}
					continue;
				}
				break;
			}

		}
	}
}
