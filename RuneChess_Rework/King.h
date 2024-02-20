#pragma once
#include "piece.h"
#include "Rook.h"

class King : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > > boardCells);
	int GetPoint();
};
