#include "IA.h"

std::vector <sf::Vector2i> IA::Play(sf::RenderWindow* window, Board board, bool& checkmate)
{
	ChooseMove(board);
	std::vector <sf::Vector2i> move;
	move.push_back(piecePos);
	move.push_back(bestMove);
	return move;
}

void IA::writeBoard(std::vector<std::vector<Cell*>> boardCells)
{
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
	for (int line = 0; line < boardCells.size(); line++)
	{
		
		std::cout << "|";
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			Piece* piece = boardCells[line][col]->GetPiece();
			if (piece == nullptr)
			{
				std::cout << "      ";
			}
			else
			{
				char w = piece->white ? 'w' : 'b';
				std::cout << piece->character << " " << piece->pos.x << piece->pos.y << " " << w;
			};
			std::cout << "|";
		}
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}
}

void IA::ChooseMove(Board board)
{
	std::vector<std::vector<Cell*>> cells = MakeBoardCopy(board.GetBoard());
	MiniMax(cells, -99999, 99999, ite, false);
}

std::vector<std::vector<Cell*>> IA::MakeBoardCopy(std::vector<std::vector<Cell*>> cellsToCopy)
{
	std::vector<std::vector<Cell*>> cells = cellsToCopy;
	for (int line = 0; line < cells.size(); line++)
	{
		std::vector<Cell*> lines;
		for (int col = 0; col < cells[line].size(); col++)
		{
			Cell* newCell = new Cell(cells[line][col]->GetRect());
			if (cells[line][col]->GetPiece() != nullptr)
			{
				Piece* pieceToCopy = cells[line][col]->GetPiece();
				Piece* newPiece = new Piece();
				switch (toupper(pieceToCopy->character))
				{
				case('K'):
					newPiece = new King();
					break;
				case('Q'):
					newPiece = new Queen();
					break;
				case('B'):
					newPiece = new Bishop();
					break;
				case('N'):
					newPiece = new Knight();
					break;
				case('R'):
					newPiece = new Rook();
					break;
				default:
					newPiece = new Pawn();
					break;
				}
				newPiece->asMove = pieceToCopy->asMove;
				newPiece->pos = pieceToCopy->pos;
				newPiece->white = pieceToCopy->white;
				newPiece->character = pieceToCopy->character;
				newPiece->possibleMoves = pieceToCopy->possibleMoves;
				newPiece->currentCell = newCell;
				newCell->SetPiece(newPiece);
			}
			else
			{
				newCell->SetPiece(nullptr);
			}

			cells[line][col] = newCell;
		}
	}
	return cells;
}

int IA::MiniMax(std::vector<std::vector<Cell*>> cells,int alpha, int beta, int iteration, bool isWhite)
{
	if (iteration <= 0)
	{
		return countPoint(cells);
	}
	int eval = isWhite ? -99999 : 99999;
	int newEval = eval;

	for (int line = 0; line < cells.size(); line++)
	{
		for (int col = 0; col < cells[line].size(); col++)
		{
			Piece* piece = cells[line][col]->GetPiece();
			if(piece != nullptr && piece->white == isWhite)
			{
				std::vector<std::vector<Cell*>> cellsCopy = MakeBoardCopy(cells);
				//copy board
				piece->possibleMoves.clear();
				piece->CalculatePossibleMove(cellsCopy);

				
				if (iteration == ite)
				{
					writeBoard(cellsCopy);
				}

				if (piece->possibleMoves.size() != 0)
				{

					for (int y = 0; y < piece->possibleMoves.size(); y++)
					{
						//make_move
						TestMove(&cells, piece , piece->possibleMoves[y]);//do move
						newEval = isWhite ? std::max(eval, MiniMax(cells,alpha,beta, iteration - 1, false)) : std::min(eval, MiniMax(cells, alpha, beta, iteration - 1, true));

						// rollback
						cells = cellsCopy;
						Piece* piece = cells[line][col]->GetPiece();

						//evaluate
						if (newEval != eval && iteration == ite)
						{
							bestMove = piece->possibleMoves[y];
							piecePos = cells[line][col]->GetPiece()->pos;
						}

						eval = newEval;

						if(isWhite)
						{
							alpha = std::max(alpha, eval);
						}
						else
						{
							beta = std::min(beta, eval);
						}
						
						if(beta <= alpha)
						{
							break;
						}
					}
				}
			}
		}
	}
	return eval;
}

int IA::countPoint(std::vector<std::vector<Cell*>> cells)
{
	int result = 0;
	for (std::vector<Cell*> line : cells)
	{
		for (Cell* cell : line)
		{
			Piece* piece = cell->GetPiece();
			if (piece != nullptr)
			{
				result += piece->white? piece->GetPoint(): -piece->GetPoint();
			}
		}
	}
	return result;
}

void IA::TestMove(std::vector<std::vector<Cell*>>* cells, Piece* piece, sf::Vector2i move)
{
	int column = move.x;
	//roc
	if ((*cells)[move.y][move.x]->GetPiece() != nullptr && piece->white == (*cells)[move.y][move.x]->GetPiece()->white)
	{
		int colSelected = piece->pos.x;
		column = move.x < colSelected ? ++column : --column;
		Piece* piece = (*cells)[move.y][move.x]->GetPiece();

		piece->asMove = true;

		piece->pos.x = move.x < colSelected ? piece->pos.x - 1 : piece->pos.x + 1;

		piece->currentCell = (*cells)[piece->pos.y][piece->pos.x];
		(*cells)[move.y][move.x]->SetPiece(nullptr);
		(*cells)[piece->pos.y][piece->pos.x]->SetPiece(piece);
	}

	piece->pos = sf::Vector2i(column, move.y);
	piece->asMove = true;

	(*cells)[move.y][column]->SetPiece(piece);
	piece->currentCell->SetPiece(nullptr);

	piece->currentCell = (*cells)[move.y][column];


	if (typeid(*piece) == typeid(Pawn) && ((piece->white && move.y == 7) || (!piece->white && move.y == 0)))
	{
		Piece* newPiece = new Queen();
		newPiece->white = piece->white;
		newPiece->asMove = true;
		newPiece->pos = piece->pos;
		newPiece->currentCell = piece->currentCell;
		newPiece->character = piece->white ? 'q' : 'Q';
		piece = newPiece;
	}
}