#pragma once
#include "piece.h"
#include "Rook.h"

class King : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};

