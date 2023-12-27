#pragma once
#include "piece.h"

class Pawn : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};

