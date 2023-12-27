#include "King.h"

void King::ShowMove(std::vector<std::vector<Cell*>>* boardCells)
{
	for(int i = -1;i<2;i++)
	{
		for(int y = -1; y < 2; y++)
		{
			if (pos.x + i > 0 && pos.x + i < (*boardCells).size() && pos.y + y > 0 && pos.y + y < (*boardCells)[pos.x + i].size() && (*boardCells)[pos.x + i][pos.y + y]->GetPiece() == nullptr)
			{
				possibleMove.push_back(sf::Vector2i(
					pos.x + i,
					pos.y + y)
				);
			}
		}
	}
}
