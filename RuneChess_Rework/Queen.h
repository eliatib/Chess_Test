#pragma once
#include "piece.h"

class Queen : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > > boardCells);
	int GetPoint();
};
