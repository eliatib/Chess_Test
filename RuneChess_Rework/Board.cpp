#include "Board.h"

Board::~Board()
{
}

Board::Board(int width, int height, sf::RenderWindow* window)
{
	gameWindow = window;
	createBoard(width, height);
	createPieces();
	InitializeMoves();
}

void Board::Display(Piece* SelectedPiece)
{
	for (int line = 0; line < boardCells.size(); line++)
	{
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			Cell cell = boardCells[line][col];
			//Squares
			gameWindow->draw(cell.GetRect());
			//Pieces
			Piece* piece = cell.GetPiece();
			if (piece != nullptr)
			{
				sf::Sprite sprite = piece->pieceSprite;
				sprite.setPosition(cell.GetRect().getPosition().x + 10, cell.GetRect().getPosition().y + 10);
				gameWindow->draw(sprite);
			}
			//Move
			if (SelectedPiece != nullptr)
			{
				sf::Vector2i pos = sf::Vector2i(col, line);
				std::vector< sf::Vector2i > moves = SelectedPiece->possibleMoves;
				if (std::find(moves.begin(), moves.end(), pos) != moves.end())
				{
					gameWindow->draw(cell.GetCircle());
				}
			}
		}
	}
}

void Board::DisplayPromotion(Piece* SelectedPiece)
{
	Cell* cell = SelectedPiece->currentCell;
	sf::RectangleShape rect = cell->GetRect();
	sf::Vector2f rectSize = rect.getSize();
	sf::Vector2f startPos = rect.getPosition();
	startPos.x += (rectSize.x / 2) - (2 * rectSize.x);
	startPos.y += startPos.y <= 2 * rectSize.y ? rectSize.y : -rectSize.y;
	sf::RectangleShape background;
	background.setFillColor(sf::Color::White);
	background.setPosition(startPos);
	background.setSize(sf::Vector2f(rectSize.x * 4, rectSize.y));
	gameWindow->draw(background);
	for (int i = 0; i < SpritePromotion.size(); i++)
	{
		SpritePromotion[i].setPosition(startPos.x + (i * rectSize.x), startPos.y);
		gameWindow->draw(SpritePromotion[i]);
	}
}

bool Board::ChoosePromotion(Piece* SelectedPiece, float x, float y, bool* isWhite, bool& checkmate)
{
	sf::Vector2f size = sf::Vector2f(pieceTexture.getSize().x / 6, pieceTexture.getSize().y / 2);
	for (int i = 0; i < SpritePromotion.size(); i++)
	{
		sf::Vector2f pos = SpritePromotion[i].getPosition();
		if (pos.x < x && pos.x + (size.x / 2) > x && pos.y < y && pos.y + (size.y / 2) > y)
		{
			Piece* piece = new Piece();
			switch (i)
			{
			case 0:
				piece = new Queen();
				break;
			case 1:
				piece = new Bishop();
				break;
			case 2:
				piece = new Knight();
				break;
			case 3:
				piece = new Rook();
				break;
			}
			piece->pieceSprite = SpritePromotion[i];
			piece->pos = SelectedPiece->pos;
			piece->asMove = true;
			piece->white = SelectedPiece->white;
			piece->currentCell = SelectedPiece->currentCell;
			SelectedPiece->currentCell->SetPiece(piece);
			SpritePromotion.clear();
			for (int i = 0; i < kingsPiece.size(); i++)
			{
				if (*isWhite != kingsPiece[i]->white)
				{
					checkmate = VerifyAllMove(kingsPiece[i]);
				}
			}
			if (isWhite != nullptr)
			{
				*isWhite = !(*isWhite);
			}

			return false;
		}
	}
	return true;
}

Piece* Board::SelectPiece(bool isWhite, float x, float y)
{
	for (std::vector < Cell > cellLine : boardCells)
	{
		for (Cell cell : cellLine)
		{
			sf::RectangleShape rect = cell.GetRect();
			sf::Vector2f pos = rect.getPosition();
			sf::Vector2f size = rect.getSize();
			if (pos.x < x && pos.x + size.x > x && pos.y < y && pos.y + size.y > y)
			{
				Piece* piece = cell.GetPiece();
				if (piece != nullptr && piece->white == isWhite)
				{
					piece->pieceSprite.setColor(sf::Color(255, 255, 255, 128));
					for (sf::Vector2i move : piece->possibleMoves)
					{
						boardCells[move.y][move.x].SetShowMove(true);
					}
					return piece;
				}
				return nullptr;
			}
		}
	}
	return nullptr;
}

void Board::DeselectPiece(Piece* piece)
{
	piece->pieceSprite.setColor(sf::Color(255, 255, 255, 255));
	for (int i = 0; i < piece->possibleMoves.size(); i++)
	{
		sf::Vector2i pos = piece->possibleMoves[i];
		boardCells[pos.y][pos.x].SetShowMove(false);
	}
}

bool Board::MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece, bool& checkmate)
{
	for (int line = 0; line < boardCells.size(); line++)
	{
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			sf::RectangleShape rect = boardCells[line][col].GetRect();
			sf::Vector2f pos = rect.getPosition();
			sf::Vector2f size = rect.getSize();
			if (pos.x < x && pos.x + size.x > x && pos.y < y && pos.y + size.y > y && boardCells[line][col].GetShowMove())
			{
				int column = col;
				//roc
				if (boardCells[line][col].GetPiece() != nullptr && SelectedPiece->white == boardCells[line][col].GetPiece()->white)
				{
					int colSelected = SelectedPiece->pos.x;
					column = col < colSelected ? ++column : --column;
					Piece* piece = boardCells[line][col].GetPiece();

					SelectedPiece->asMove = true;

					piece->pos.x = col < colSelected ? SelectedPiece->pos.x - 1 : SelectedPiece->pos.x + 1;

					piece->currentCell = &boardCells[piece->pos.y][piece->pos.x];
					boardCells[line][col].SetPiece(nullptr);
					boardCells[piece->pos.y][piece->pos.x].SetPiece(piece);
				}
				SelectedPiece->pos = sf::Vector2i(column, line);
				SelectedPiece->asMove = true;

				boardCells[line][column].SetPiece(SelectedPiece);
				SelectedPiece->currentCell->SetPiece(nullptr);

				SelectedPiece->currentCell = &boardCells[line][column];

				if (typeid(*SelectedPiece) == typeid(Pawn))
				{
					if ((SelectedPiece->white && SelectedPiece->pos.y + 1 == boardSize.y)
						|| (!SelectedPiece->white && SelectedPiece->pos.y == 0))
					{
						CreateSpritePromotion(SelectedPiece);
						return true;
					}
				}

				for (int i = 0; i < kingsPiece.size(); i++)
				{
					if (*isWhite != kingsPiece[i]->white)
					{
						checkmate = VerifyAllMove(kingsPiece[i]);
					}
				}

				if (isWhite != nullptr)
				{
					*isWhite = !(*isWhite);
				}
				return false;
			}
		}
	}
	return false;
}

void Board::MovePieceIA(bool* isWhite, Piece* pieceToMove, sf::Vector2i move, bool& checkmate)
{
	int col = move.x;
	int line = move.y;
	int column = col;
	//roc
	if (boardCells[line][col].GetPiece() != nullptr && pieceToMove->white == boardCells[line][col].GetPiece()->white)
	{
		int colSelected = pieceToMove->pos.x;
		column = col < colSelected ? ++column : --column;
		Piece* piece = boardCells[line][col].GetPiece();

		pieceToMove->asMove = true;

		piece->pos.x = col < colSelected ? pieceToMove->pos.x - 1 : pieceToMove->pos.x + 1;

		piece->currentCell = &boardCells[piece->pos.y][piece->pos.x];
		boardCells[line][col].SetPiece(nullptr);
		boardCells[piece->pos.y][piece->pos.x].SetPiece(piece);
	}
	pieceToMove->pos = sf::Vector2i(column, line);
	pieceToMove->asMove = true;

	boardCells[line][column].SetPiece(pieceToMove);
	pieceToMove->currentCell->SetPiece(nullptr);

	pieceToMove->currentCell = &boardCells[line][column];

	if (typeid(*pieceToMove) == typeid(Pawn))
	{
		if ((pieceToMove->white && pieceToMove->pos.y + 1 == boardSize.y)
			|| (!pieceToMove->white && pieceToMove->pos.y == 0))
		{
			Piece* newPiece = new Queen();
			newPiece->white = pieceToMove->white;
			newPiece->asMove = true;
			newPiece->pos = pieceToMove->pos;
			newPiece->currentCell = pieceToMove->currentCell;
			pieceToMove = newPiece;
			pieceToMove->currentCell->SetPiece(pieceToMove);
			CreateTexturePiece(pieceToMove);
		}
	}

	for (int i = 0; i < kingsPiece.size(); i++)
	{
		if (*isWhite != kingsPiece[i]->white)
		{
			checkmate = VerifyAllMove(kingsPiece[i]);
		}
	}

	if (isWhite != nullptr)
	{
		*isWhite = !(*isWhite);
	}
}

std::vector<std::vector<Cell>> Board::GetBoard()
{
	return boardCells;
}

std::vector<Piece*> Board::GetPieces()
{
	return pieces;
}

void Board::CreateTexturePiece(Piece* piece)
{
	float spriteHeight = pieceTexture.getSize().y / 2;
	float spriteWidth = pieceTexture.getSize().x / 6;
	float spriteX = 0;
	float spriteY = 0;

	if (typeid(*piece) == typeid(Queen))
	{
		spriteX = 1;
	}
	else if (typeid(*piece) == typeid(Pawn))
	{
		spriteX = 5;
	}
	spriteX *= spriteWidth;
	if (!piece->white)
	{
		spriteY = pieceTexture.getSize().y / 2;
	}

	sf::Sprite sprite;
	sprite.setTexture(pieceTexture);
	sprite.setTextureRect(sf::IntRect(spriteX, spriteY, spriteWidth, spriteHeight));
	sprite.setScale(sf::Vector2<float>(scale.x, scale.y));
	piece->pieceSprite = sprite;
}

void Board::createBoard(int width, int height)
{
	cellSize = std::min(gameWindow->getSize().x / 10, gameWindow->getSize().y / 10);
	boardSize = sf::Vector2f(width, height);
	for (int boardHeight = 0; boardHeight < height; boardHeight++)
	{
		std::vector < Cell > line;
		for (int boardWidth = 0; boardWidth < width; boardWidth++)
		{
			sf::RectangleShape rect;
			rect.setFillColor((boardHeight + boardWidth) % 2 == 0 ? sf::Color(255, 204, 153) : sf::Color(255, 229, 255));
			rect.setPosition(sf::Vector2f(
				(gameWindow->getSize().x / 2) - (cellSize * (width / 2)) + (cellSize * boardWidth),
				(gameWindow->getSize().y / 2) - (cellSize * (height / 2)) + (cellSize * boardHeight)
			));
			rect.setSize(sf::Vector2f(cellSize, cellSize));
			Cell cell = Cell(rect);
			line.push_back(cell);
		}
		boardCells.push_back(line);
	}
}

void Board::createPieces()
{
	SetTexture();
	int col{ 0 };
	int line{ 0 };
	float spriteHeight = pieceTexture.getSize().y / 2;
	float spriteWidth = pieceTexture.getSize().x / 6;
	pieceSize = sf::Vector2f(spriteWidth, spriteHeight);
	scale = sf::Vector2f(cellSize / (pieceSize.x * 1.3), cellSize / (pieceSize.y * 1.3));
	for (char c : FEN)
	{
		float spriteX = 0;
		float spriteY = 0;

		//if it's a number
		if (isdigit(c))
		{
			//char is transform in Ascii equivalent (48 corespond to the '0' on ascii table so we substract it to get the digit in integer)
			int n = c - 48;
			col += n;
		}
		//if it's sign "/" we change of line
		else if (c == '/')
		{
			line++;
			col = 0;
		}
		//if it's a character it's a piece
		else
		{
			bool isWhite = true;
			if (isupper(c))
			{
				spriteY = pieceTexture.getSize().y / 2;
				isWhite = false;
			}
			Piece* piece = new Piece();
			switch (toupper(c))
			{
			case('K'):
				piece = new King();
				break;
			case('Q'):
				piece = new Queen();
				spriteX = 1;
				break;
			case('B'):
				piece = new Bishop;
				spriteX = 2;
				break;
			case('N'):
				piece = new Knight();
				spriteX = 3;
				break;
			case('R'):
				piece = new Rook;
				spriteX = 4;
				break;
			default:
				piece = new Pawn();
				spriteX = 5;
				break;
			}

			spriteX *= spriteWidth;
			sf::Sprite sprite;
			sprite.setTexture(pieceTexture);
			sprite.setTextureRect(sf::IntRect(spriteX, spriteY, spriteWidth, spriteHeight));
			sprite.setScale(sf::Vector2<float>(scale.x, scale.y));
			piece->pieceSprite = sprite;
			piece->white = isWhite;
			piece->pos = sf::Vector2i(col, line);
			piece->currentCell = &boardCells[line][col];
			if (typeid(*piece) == typeid(King))
			{
				kingsPiece.push_back(piece);
			}
			pieces.push_back(piece);
			boardCells[line][col].SetPiece(piece);
			col++;
		}
	}
}

void Board::SetTexture()
{
	if (!pieceTexture.loadFromFile("img/Pieces.png"))
	{
		std::cout << "No file found for textures" << std::endl;
	}
}

void Board::CreateSpritePromotion(Piece* selectedPiece)
{
	int col{ 0 };
	int line{ 0 };
	std::vector<sf::Sprite> sprites(4);
	float spriteHeight = pieceSize.y;
	float spriteWidth = pieceSize.x;
	float spriteY = selectedPiece->white ? 0 : pieceSize.y;
	for (int i = 0; i < sprites.size(); i++)
	{
		float spriteX = spriteWidth * (1 + i);
		sf::Sprite sprite;
		sprite.setTexture(pieceTexture);
		sprite.setTextureRect(sf::IntRect(spriteX, spriteY, pieceSize.x, pieceSize.y));
		sprite.setScale(sf::Vector2<float>(scale.x, scale.y));
		sprites[i] = sprite;
	}
	SpritePromotion = sprites;
}

bool Board::VerifyKingNotinCheck(Piece* king, sf::Vector2i kingPos, sf::Vector2i pos = sf::Vector2i(-1, -1), sf::Vector2i move = sf::Vector2i(-1, -1))
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
					line + (i * down) >= 0 && line + (i * down) < boardCells.size() && col + (i * right) >= 0 && col + (i * right) < boardCells[line + (i * down)].size();
					i++)
				{
					int y = line + (i * down);
					int x = col + (i * right);
					Piece* piece = boardCells[y][x].GetPiece();
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
				line + (i * down) >= 0 && line + (i * down) < boardCells.size() && col + (i * right) >= 0 && col + (i * right) < boardCells[line + (i * down)].size();
				i++
				)
			{
				int x = col + (i * right);
				int y = line + (i * down);
				Piece* piece = boardCells[y][x].GetPiece();
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
		if (y >= 0 && y < boardCells.size())
		{
			int dec = std::abs(i) == 2 ? 1 : std::abs(i) == 1 ? 2 : -1;

			for (int j = -1 * dec; j <= 1 * dec; j = j + (2 * dec))
			{
				int x = col + j;

				if (x >= 0 && x < boardCells[y].size())
				{
					Piece* piece = boardCells[y][x].GetPiece();
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

bool Board::VerifyAllMove(Piece* king)
{
	bool checkmate = true;
	for (std::vector < Cell > cellLine : boardCells)
	{
		for (Cell cell : cellLine)
		{
			Piece* piece = cell.GetPiece();
			if (piece != nullptr && piece->white == king->white)
			{
				piece->possibleMoves.clear();
				piece->CalculatePossibleMove(&boardCells);
				std::vector< sf::Vector2i >* possibleMoves = &piece->possibleMoves;
				sf::Vector2i pos = piece->pos;
				int i = 0;
				while (i < possibleMoves->size())
				{
					bool fCheck;
					if (typeid(*piece) == typeid(King))
					{
						fCheck = VerifyKingNotinCheck(king, (*possibleMoves)[i], pos, (*possibleMoves)[i]);
					}
					else
					{
						fCheck = VerifyKingNotinCheck(king, king->pos, pos, (*possibleMoves)[i]);
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

void Board::InitializeMoves()
{
	for (std::vector < Cell > cellLine : boardCells)
	{
		for (Cell cell : cellLine)
		{
			Piece* piece = cell.GetPiece();
			if (piece != nullptr)
			{
				piece->CalculatePossibleMove(&boardCells);
			}
		}
	}
}