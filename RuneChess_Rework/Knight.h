#pragma once
#include "piece.h"

class Knight : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > >* boardCells);
	int GetPoint();
};
