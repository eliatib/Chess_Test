#pragma once
#include "piece.h"

class Pawn : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > >* boardCells);
	int GetPoint();
};
