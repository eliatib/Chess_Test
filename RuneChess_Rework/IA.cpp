#include "IA.h"

std::vector <sf::Vector2i> IA::Play(sf::RenderWindow* window, Board board, bool* isWhite, bool& checkmate)
{
	ChooseMove(board);
	std::vector <sf::Vector2i> move;
	move.push_back(piecePos);
	move.push_back(bestMove);
	return move;
}

void IA::ChooseMove(Board board)
{
	std::vector<Piece*> pieces = board.GetPieces();
	MiniMax(board, board->GetBoard(), pieces, ite, false);
}

int IA::MiniMax(Board* board, std::vector<std::vector<Cell>> cells, std::vector<Piece*> pieces, int iteration, bool isWhite)
{
	if (iteration <= 0)
	{
		return countPoint(cells);
	}
	int eval = isWhite ? -99999 : 99999;
	int newEval = eval;
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->white == isWhite)
		{
			pieces[i]->possibleMoves.clear();
			pieces[i]->CalculatePossibleMove(&cells);
			std::vector<std::vector<Cell>> copy = cells;
			//copy piece element
			sf::Vector2i copyPos = pieces[i]->pos;
			bool copyAsMove = pieces[i]->asMove;
			bool isPawn = false;
			if (typeid(*pieces[i]) == typeid(Pawn))
			{
				isPawn = true;
			}

			if (pieces[i]->possibleMoves.size() != 0)
			{
				for (int y = 0; y < pieces[i]->possibleMoves.size(); y++)
				{
					//std::cout << "pos :" << copyPos.x << " " << copyPos.y << " move : " << pieces[i]->possibleMoves[y].x << " " << pieces[i]->possibleMoves[y].y << " " << iteration << std::endl;
					TestMove(&cells, pieces[i], pieces[i]->possibleMoves[y]);//do move

					newEval = isWhite ? std::max(eval, MiniMax(board, cells, pieces, iteration - 1, !isWhite)) : std::min(eval, MiniMax(board, cells, pieces, iteration - 1, !isWhite));

					if (pieces[i]->possibleMoves.size() != 0 && newEval != eval && iteration == ite)
					{
						bestMove = pieces[i]->possibleMoves[y];
						pieceToMove = pieces[i];
					}

					eval = newEval;

					cells = copy; //undo move
					pieces[i]->pos = copyPos;
					pieces[i]->asMove = copyAsMove;
					if (isPawn)
					{
						Piece* newPiece = new Pawn();
						newPiece->white = pieces[i]->white;
						newPiece->asMove = pieces[i]->asMove;
						newPiece->pos = pieces[i]->pos;
						newPiece->currentCell = pieces[i]->currentCell;
						pieces[i] = newPiece;
						pieces[i]->currentCell->SetPiece(pieces[i]);
						board->CreateTexturePiece(pieces[i]);
						pieces[i]->possibleMoves.clear();
						pieces[i]->CalculatePossibleMove(&cells);
					}
				}
			}
		}
	}
	return eval;
}

int IA::countPoint(std::vector<std::vector<Cell>> cells)
{
	int result = 0;
	for (std::vector<Cell> line : cells)
	{
		for (Cell cell : line)
		{
			Piece* piece = cell.GetPiece();
			if (piece != nullptr)
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
	if (typeid(*piece) == typeid(Pawn) && ((piece->white && move.y == 7) || (!piece->white && move.y == 0)))
	{
		Piece* newPiece = new Queen();
		newPiece->white = piece->white;
		newPiece->asMove = true;
		piece = newPiece;
	}
	if (!piece->asMove)
	{
		piece->asMove = true;
	}
	(*cells)[move.y][move.x].SetPiece(piece);
	piece->pos = move;
}