#pragma once
#include "piece.h"

class Rook : public Piece
{
public:
	void ShowMove(std::vector< std::vector< Cell* > >* boardCells);

};