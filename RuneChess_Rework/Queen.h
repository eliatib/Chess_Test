#pragma once
#include "piece.h"

class Queen : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};
