#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	void CalculatePossibleMove(std::vector< std::vector< Cell* > >* boardCells);
};
