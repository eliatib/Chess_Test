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

void IA::recreatePiece(std::vector<std::vector<Cell*>>* cells, char c, sf::Vector2i pos, bool isWhite, bool asMove)
{
	Piece* newPiece = new Piece();
	switch (toupper(c))
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

	newPiece->white = isWhite;
	newPiece->asMove = asMove;
	newPiece->pos = pos;
	newPiece->character = c;
	newPiece->currentCell = (*cells)[pos.y][pos.x];
	newPiece->currentCell->SetPiece(newPiece);
	newPiece->possibleMoves.clear();
	newPiece->CalculatePossibleMove(cells);
}

void IA::ChooseMove(Board board)
{
	std::vector<std::vector<Cell*>> cells = board.GetBoard();
	for (int line = 0; line < cells.size(); line++)
	{
		std::vector<Cell*> lines;
		for (int col = 0; col < cells[line].size(); col++)
		{
			Cell* newCell = new Cell(cells[line][col]->GetRect());
			if(cells[line][col]->GetPiece() != nullptr)
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
				newPiece->currentCell = newCell;
				newCell->SetPiece(newPiece);
			}

			cells[line][col] = newCell;
		}
	}
	writeBoard(cells);
	MiniMax(cells, ite, false);
	writeBoard(cells);
}

int IA::MiniMax(std::vector<std::vector<Cell*>> cells, int iteration, bool isWhite)
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
				//copy piece element
				sf::Vector2i copyPos = piece->pos;
				bool copyAsMove = piece->asMove;
				bool copyWhite = piece->white;
				char copyType = piece->character;

				std::vector< sf::Vector2i > copyPossibleMoves = piece->possibleMoves;

				if (piece->possibleMoves.size() != 0)
				{
					for (int y = 0; y < copyPossibleMoves.size(); y++)
					{
						sf::Vector2i copyEPPos;
						bool copyEPAsMove = false;
						bool copyEPWhite = false;
						char copyEPType = ' ';
						if (cells[copyPossibleMoves[y].y][copyPossibleMoves[y].x]->GetPiece() != nullptr)
						{
							Piece* eatenPiece = cells[copyPossibleMoves[y].y][copyPossibleMoves[y].x]->GetPiece();
							copyEPPos = eatenPiece->pos;
							copyEPAsMove = eatenPiece->asMove;
							copyEPWhite = eatenPiece->white;
							copyEPType = eatenPiece->character;
						}
						
						if(piece->character == 'P' && piece->pos.x == 7 && copyPossibleMoves[y].x == 7)
						{
							std::cout;
						}
						TestMove(&cells, piece , copyPossibleMoves[y]);//do move

						newEval = isWhite ? std::max(eval, MiniMax(cells, iteration - 1, false)) : std::min(eval, MiniMax(cells, iteration - 1, true));

						if (copyPossibleMoves.size() != 0 && newEval != eval && iteration == ite)
						{
							bestMove = copyPossibleMoves[y];
							piecePos = copyPos;
						}

						eval = newEval;

						if (copyEPType != ' ')
						{
							recreatePiece(&cells, copyEPType, copyEPPos, copyEPWhite, copyEPAsMove);
						}
						else
						{
							cells[copyPossibleMoves[y].y][copyPossibleMoves[y].x]->SetPiece(nullptr);
						}

						recreatePiece(&cells, copyType, copyPos, copyWhite, copyAsMove);

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