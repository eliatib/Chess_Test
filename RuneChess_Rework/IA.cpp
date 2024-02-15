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
			piece->possibleMoves.clear();
			piece->CalculatePossibleMove(&cells);
		}
	}

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
							copyEPAsMove = eatenPiece->asMove;
							copyEPWhite = eatenPiece->white;
							copyEPType = eatenPiece->character;
						}
						
						TestMove(&cells, piece ,piece->possibleMoves[y]);//do move

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

bool IA::VerifyKingNotinCheck(Piece* king, std::vector<std::vector<Cell*>> cells, sf::Vector2i kingPos, sf::Vector2i pos = sf::Vector2i(-1, -1), sf::Vector2i move = sf::Vector2i(-1, -1))
{
	int line = kingPos.y;
	int col = kingPos.x;
	//R,Q
	for (int right = -1; right < 2; right++)
	{
		for (int down = -1; down < 2; down++)
		{
			if ((right != 0 || down != 0) && (right == 0 || down == 0))
			{
				for (int i = 1;
					line + (i * down) >= 0 && line + (i * down) < cells.size() && col + (i * right) >= 0 && col + (i * right) < cells[line + (i * down)].size();
					i++)
				{
					int y = line + (i * down);
					int x = col + (i * right);
					Piece* piece = cells[y][x]->GetPiece();
					if (piece == nullptr || (x == pos.x && y == pos.y))
					{
						continue;
					}
					else if (x == move.x && y == move.y)
					{
						break;
					}
					else if ((typeid(*piece) == typeid(Rook) || typeid(*piece) == typeid(Queen)) && piece->white != king->white)
					{
						return true;
					}
					break;
				}
			}
		}
	}
	//P,B,Q
	for (int right = -1; right < 2; right += 2)
	{
		for (int down = -1; down < 2; down += 2)
		{
			for (
				int i = 1;
				line + (i * down) >= 0 && line + (i * down) < cells.size() && col + (i * right) >= 0 && col + (i * right) < cells[line + (i * down)].size();
				i++
				)
			{
				int x = col + (i * right);
				int y = line + (i * down);
				Piece* piece = cells[y][x]->GetPiece();
				if (piece == nullptr || (x == pos.x && y == pos.y))
				{
					continue;
				}
				else
				{
					int sens = piece->white ? 1 : -1;
					if (x == move.x && y == move.y)
					{
						break;
					}
					else if ((typeid(*piece) == typeid(Bishop) || typeid(*piece) == typeid(Queen) || (i == 1 && typeid(*piece) == typeid(Pawn) && down == sens)) && piece->white != king->white)
					{
						return true;
					}
				}
				break;
			}
		}
	}
	//N
	for (int i = -2; i <= 2; i++)
	{
		int y = line + i;
		if (y >= 0 && y < cells.size())
		{
			int dec = std::abs(i) == 2 ? 1 : std::abs(i) == 1 ? 2 : -1;

			for (int j = -1 * dec; j <= 1 * dec; j = j + (2 * dec))
			{
				int x = col + j;

				if (x >= 0 && x < cells[y].size())
				{
					Piece* piece = cells[y][x]->GetPiece();
					if (piece == nullptr)
					{
						continue;
					}
					else if (typeid(*piece) == typeid(Knight) && piece->white != king->white)
					{
						return true;
					}
					break;
				}
			}
		}
	}
	return false;
}

bool IA::VerifyAllMove(Piece* king, std::vector<std::vector<Cell*>> cells)
{
	bool checkmate = true;
	for (std::vector < Cell* > cellLine : cells)
	{
		for (Cell* cell : cellLine)
		{
			Piece* piece = cell->GetPiece();
			if (piece != nullptr && piece->white == king->white)
			{
				piece->possibleMoves.clear();
				piece->CalculatePossibleMove(&cells);
				std::vector< sf::Vector2i >* possibleMoves = &piece->possibleMoves;
				sf::Vector2i pos = piece->pos;
				int i = 0;
				while (i < possibleMoves->size())
				{
					bool fCheck;
					if (typeid(*piece) == typeid(King))
					{
						fCheck = VerifyKingNotinCheck(king,cells, (*possibleMoves)[i], pos, (*possibleMoves)[i]);
					}
					else
					{
						fCheck = VerifyKingNotinCheck(king,cells, king->pos, pos, (*possibleMoves)[i]);
					}
					if (fCheck)
					{
						possibleMoves->erase(possibleMoves->begin() + i);
						continue;
					}
					i++;
				}

				if (!possibleMoves->empty())
				{
					checkmate = false;
				}
			}
		}
	}
	return checkmate;
}