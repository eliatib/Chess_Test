#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};

