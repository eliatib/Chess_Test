#include "IA.h"

std::vector <sf::Vector2i> IA::Play(sf::RenderWindow* window, Board board, bool& checkmate)
{
	std::cout << "begin";
	ChooseMove(board);
	std::vector <sf::Vector2i> move;
	move.push_back(piecePos);
	move.push_back(bestMove);
	std::cout << " end";
	return move;
}

void IA::writeBoard(std::vector<std::vector<Cell*>> boardCells)
{
	for (int line = 0; line < boardCells.size(); line++)
	{
		std::cout << "--------------------------------------------------------------" << std::endl;
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			Piece* piece = boardCells[line][col]->GetPiece();
			if (piece == nullptr)
			{
				std::cout << " ";
			}
			else
			{
				char w = piece->white ? 'w' : 'b';
				std::cout << piece->character << " " << piece->pos.x << piece->pos.y << " " << w;
			};
			std::cout << "|";
		}
		std::cout << std::endl;
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
	std::vector<Piece*> pieces;

	std::vector<std::vector<Cell*>> cells;
	for (std::vector<Cell*> line : board.GetBoard())
	{
		std::vector<Cell*> lines;
		for (Cell* cell : line)
		{
			Cell* newCell = new Cell(cell->GetRect());
			lines.push_back(newCell);
		}
		cells.push_back(lines);
	}
	std::vector<Piece*> ppieces = board.GetPieces();
	for (int i = 0;i < ppieces.size();i++)
	{
		Piece* newPiece = new Piece();
		switch (toupper(ppieces[i]->character))
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
		newPiece->asMove = ppieces[i]->asMove;
		newPiece->pos = ppieces[i]->pos;
		newPiece->white = ppieces[i]->white;
		newPiece->character = ppieces[i]->character;

		pieces.push_back(newPiece);
		cells[pieces[i]->pos.y][pieces[i]->pos.x]->SetPiece(pieces[i]);
		pieces[i]->currentCell = cells[pieces[i]->pos.y][pieces[i]->pos.x];
	}
	writeBoard(cells);
	MiniMax(cells, ite, false);
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
				piece->possibleMoves.clear();
				piece->CalculatePossibleMove(&cells);
				for( sf::Vector2i move : piece->possibleMoves)
				{
					std::cout << "(" << move.x << "," << move.y << "),";
				}
				std::cout << "f" << std::endl;
				//copy piece element
				sf::Vector2i copyPos = piece->pos;
				bool copyAsMove = piece->asMove;
				bool copyWhite = piece->white;
				char copyType = piece->character;

				if (piece->possibleMoves.size() != 0)
				{
					for (int y = 0; y < piece->possibleMoves.size(); y++)
					{
						sf::Vector2i copyEPPos;
						bool copyEPAsMove = false;
						bool copyEPWhite = false;
						char copyEPType = ' ';
						if (cells[piece->possibleMoves[y].y][piece->possibleMoves[y].x]->GetPiece() != nullptr)
						{
							Piece* eatenPiece = cells[piece->possibleMoves[y].y][piece->possibleMoves[y].x]->GetPiece();
							copyEPPos = eatenPiece->pos;
							bool copyEPAsMove = eatenPiece->asMove;
							bool copyEPWhite = eatenPiece->white;
							char copyEPType = eatenPiece->character;
						}
						
						if (piece->possibleMoves[y].x == 1 && piece->possibleMoves[y].y == 2 && toupper(piece->character) == 'N')
						{
							std::cout << "haaa";
						}
						TestMove(&cells, piece ,piece->possibleMoves[y]);//do move

						std::cout << " NEW Move ----------------- " << std::endl;
						std::cout << " " << std::endl;
						writeBoard(cells); 

						newEval = isWhite ? std::max(eval, MiniMax(cells, iteration - 1, false)) : std::min(eval, MiniMax(cells, iteration - 1, true));

						if (piece->possibleMoves.size() != 0 && newEval != eval && iteration == ite)
						{
							bestMove = piece->possibleMoves[y];
							piecePos = copyPos;
						}

						eval = newEval;

						if (copyEPType != ' ')
						{
							recreatePiece(&cells, copyEPType, copyEPPos, copyEPWhite, copyEPAsMove);
						}
						else
						{
							cells[piece->possibleMoves[y].y][piece->possibleMoves[y].x]->SetPiece(nullptr);
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
				result += piece->GetPoint();
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

	if (typeid(*piece) == typeid(Pawn) && ((piece->white && move.y == 7) || (!piece->white && move.y == 0)))
	{
		Piece* newPiece = new Queen();
		newPiece->white = piece->white;
		newPiece->asMove = true;
		piece = newPiece;
	}

	piece->pos = sf::Vector2i(column, move.y);
	piece->asMove = true;

	(*cells)[move.y][column]->SetPiece(piece);
	piece->currentCell->SetPiece(nullptr);

	piece->currentCell = (*cells)[move.y][column];
	(*cells)[piece->pos.y][piece->pos.x]->SetPiece(nullptr);
}