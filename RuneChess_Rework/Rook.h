#pragma once
#include "piece.h"

class Rook : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > >* boardCells);
	int GetPoint();
};