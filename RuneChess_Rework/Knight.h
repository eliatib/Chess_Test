#pragma once
#include "piece.h"

class Knight : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};

