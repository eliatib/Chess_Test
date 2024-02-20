#include "Pawn.h"

void Pawn::CalculatePossibleMove(std::vector< std::vector< Cell* > > boardCells)
{
	int move = white ? 1 : -1;
	if (!asMove && boardCells[pos.y + (move * 2)][pos.x]->GetPiece() == nullptr && boardCells[pos.y + (move)][pos.x]->GetPiece() == nullptr)
	{
		possibleMoves.push_back(sf::Vector2i(
			pos.x,
			pos.y + (move * 2)
		));
	}

	for (int i = -1; i < 2; i++)
	{
		if (pos.x + i >= 0 && pos.x + i < boardCells[pos.y].size() && pos.y + move >= 0 && pos.y + move < boardCells.size())
		{
			Piece* piece = boardCells[pos.y + move][pos.x + i]->GetPiece();
			if (
				(i == 0 && piece == nullptr)
				|| (i != 0 && piece != nullptr && piece->white != white)
				)
				possibleMoves.push_back(sf::Vector2i(
					pos.x + i,
					pos.y + move));
		}
	}
}

int Pawn::GetPoint()
{
	return 1;
}
