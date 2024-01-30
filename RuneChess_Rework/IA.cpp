#include "IA.h"

void IA::Play(sf::RenderWindow* window, Board* board, bool* isWhite,bool& checkmate)
{
	ChooseMove(board);
	board->MovePiece(isWhite, bestMove.x, bestMove.y, pieceToMove, checkmate);
}

void IA::ChooseMove(Board* board)
{
	std::vector<Piece*> pieces = board->GetPieces();
	MiniMax(board->GetBoard(),pieces, 3, true);
}

int IA::MiniMax(std::vector<std::vector<Cell>> cells, std::vector<Piece*> pieces,  int iteration, bool isWhite)
{
	if (iteration <= 0)
	{
		return countPoint(cells);
	}
	int eval = isWhite ? -99999 : 99999;
	int newEval = eval;
	for(Piece* piece : pieces)
	{
		if(piece->white == isWhite)
		{
			piece->CalculatePossibleMove(&cells);
			std::vector<std::vector<Cell>> copy = cells; 
			sf::Vector2i copyPos = piece->pos;
			for(sf::Vector2i move : piece->possibleMoves)
			{
				TestMove(&cells, piece, move);//do move

				newEval = isWhite ? std::max(eval, MiniMax(cells, pieces, iteration - 1, !isWhite)) : std::min(eval, MiniMax(cells, pieces, iteration - 1, !isWhite));

				if(newEval != eval)
				{
					bestMove = move;
					pieceToMove = piece;
				}

				eval = newEval;

				cells = copy; //undo move
				piece->pos = copyPos;
			}
		}
	}
	return eval;
}

int IA::countPoint(std::vector<std::vector<Cell>> cells)
{
	int result = 0;
	for(std::vector<Cell> line : cells)
	{
		for(Cell cell : line)
		{
			Piece* piece = cell.GetPiece();
			if(piece != nullptr)
			{
				result += piece->GetPoint();
			}
		}
	}
	return result;
}

void IA::TestMove(std::vector<std::vector<Cell>>* cells, Piece* piece, sf::Vector2i move)
{
	(*cells)[piece->pos.y][piece->pos.x].SetPiece(nullptr);
	(*cells)[move.y][move.x].SetPiece(piece);
	piece->pos = move;
}


