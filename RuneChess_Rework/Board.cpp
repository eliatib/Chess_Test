#include "Board.h"


Board::~Board()
{
}

void Board::Display()
{
	for(std::vector < Cell* > cellLine : boardCells)
	{
		for(Cell* cell : cellLine)
		{
			//Squares
			gameWindow->draw(cell->GetRect());
			//Pieces
			Piece* piece = cell->GetPiece();
			if (piece != nullptr)
			{
				sf::Sprite sprite = piece->pieceSprite;
				sprite.setPosition(cell->GetRect().getPosition().x + 10, cell->GetRect().getPosition().y + 10);
				gameWindow->draw(sprite);
			}
			//Move
			if(cell->GetMove() == true)
			{
				gameWindow->draw(cell->GetCircle());
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
	startPos.x += (rectSize.x / 2) - (2*rectSize.x);
	startPos.y += startPos.y <= 2 * rectSize.y ? rectSize.y : -rectSize.y;
	sf::RectangleShape background;
	background.setFillColor(sf::Color::White);
	background.setPosition(startPos);
	background.setSize(sf::Vector2f(rectSize.x*4,rectSize.y));
	gameWindow->draw(background);
	for(int i = 0; i< SpritePromotion.size();i++)
	{
		SpritePromotion[i].setPosition(startPos.x + (i * rectSize.x), startPos.y);
		gameWindow->draw(SpritePromotion[i]);
	}
}

bool Board::ChoosePromotion(Piece* SelectedPiece, float x, float y, bool* isWhite)
{
	sf::Vector2f size = sf::Vector2f(pieceTexture.getSize().x / 6, pieceTexture.getSize().y / 2);
	for (int i = 0; i < SpritePromotion.size(); i++)
	{
		sf::Vector2f pos = SpritePromotion[i].getPosition();
		if (pos.x < x && pos.x + (size.x/2) > x && pos.y < y && pos.y + (size.y/2) > y)
		{
			Piece* piece = new Piece();
			switch(i)
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
			if (isWhite != nullptr)
			{
				*isWhite = !(*isWhite);
			}
			SpritePromotion.clear();
			return false;
		}
	}
	return true;
}

Piece* Board::SelectPiece(bool isWhite, float x, float y)
{
	for (std::vector < Cell* > cellLine : boardCells)
	{
		for (Cell* cell : cellLine)
		{
			sf::RectangleShape rect = cell->GetRect();
			sf::Vector2f pos = rect.getPosition();
			sf::Vector2f size = rect.getSize();
			if(pos.x < x && pos.x + size.x > x && pos.y < y && pos.y + size.y > y)
			{
				Piece* piece = cell->GetPiece();
				if(piece != nullptr && piece->white == isWhite)
				{
					piece->pieceSprite.setColor(sf::Color(255, 255, 255, 128));
					piece->ShowMove(&boardCells);
					for(sf::Vector2i move : piece->possibleMove)
					{
						boardCells[move.y][move.x]->SetMove(true);
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
	piece->possibleMove.clear();
	for (std::vector < Cell* > cellLine : boardCells)
	{
		for (Cell* cell : cellLine)
		{
			if (cell->GetMove())
			{
				cell->SetMove(false);
			}
		}
	}
}

bool Board::MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece)
{
	for (int line =0; line < boardCells.size(); line++)
	{
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			sf::RectangleShape rect = boardCells[line][col]->GetRect();
			sf::Vector2f pos = rect.getPosition();
			sf::Vector2f size = rect.getSize();
			if (pos.x < x && pos.x + size.x > x && pos.y < y && pos.y + size.y > y && boardCells[line][col]->GetMove())
			{
				int column = col;
				//roc
				if(boardCells[line][col]->GetPiece() != nullptr && SelectedPiece->white == boardCells[line][col]->GetPiece()->white)
				{
					int colSelected = SelectedPiece->pos.x;
					column = col < colSelected ? ++column : --column;
					Piece* piece = boardCells[line][col]->GetPiece();

					SelectedPiece->asMove = true;

					piece->pos.x = col < colSelected ? SelectedPiece->pos.x - 1 : SelectedPiece->pos.x + 1;

					piece->currentCell = boardCells[piece->pos.y][piece->pos.x];
					boardCells[line][col]->SetPiece(nullptr);
					boardCells[piece->pos.y][piece->pos.x]->SetPiece(piece);
				}
				SelectedPiece->pos = sf::Vector2i(column, line);
				SelectedPiece->asMove = true;

				boardCells[line][column]->SetPiece(SelectedPiece);
				SelectedPiece->currentCell->SetPiece(nullptr);

				SelectedPiece->currentCell = boardCells[line][column];

				verifyBoardControl();

				if(typeid(*SelectedPiece) == typeid(Pawn))
				{
					if((SelectedPiece->white && SelectedPiece->pos.y + 1 == boardSize.y)
					|| (!SelectedPiece->white && SelectedPiece->pos.y == 0))
					{
						CreateSpritePromotion(SelectedPiece);
						return true;
					}
				}
				for(int i = 0;i<kingsPiece.size();i++)
				{
					if(kingsPiece[i]->white? kingsPiece[i]->currentCell->getControlled()[1] : kingsPiece[i]->currentCell->getControlled()[0])
					{
						inCheckPiece = kingsPiece[i];
						sf::Vector2i pos = inCheckPiece->pos;
						inCheckPiece->currentCell->verifyCheckMate(pos.y,pos.x,&boardCells);
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

void Board::createBoard(int width, int height)
{
	cellSize = std::min(gameWindow->getSize().x / 10, gameWindow->getSize().y / 10);
	boardSize = sf::Vector2i(width, height);
	for (int boardHeight = 0; boardHeight < height; boardHeight++)
	{
		std::vector < Cell* > line;
		for (int boardWidth = 0; boardWidth < width; boardWidth++)
		{
			sf::RectangleShape rect;
			rect.setFillColor((boardHeight + boardWidth) % 2 == 0 ? sf::Color(255, 204, 153) : sf::Color(255, 229, 255));
			rect.setPosition(sf::Vector2f(
				(gameWindow->getSize().x / 2) - (cellSize * (width / 2)) + (cellSize * boardWidth),
				(gameWindow->getSize().y / 2) - (cellSize * (height / 2)) + (cellSize * boardHeight)
			));
			rect.setSize(sf::Vector2f(cellSize, cellSize));
			Cell* cell = new Cell(rect);
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
				spriteY = pieceTexture.getSize().y/2;
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
			sprite.setScale(sf::Vector2<float>(0.5, 0.5));
			piece->pieceSprite = sprite;
			piece->white = isWhite;
			piece->pos = sf::Vector2i(col, line);
			piece->currentCell = boardCells[line][col];
			if(typeid(*piece) == typeid(King))
			{
				kingsPiece.push_back(piece);
			}
			boardCells[line][col]->SetPiece(piece);
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
	float spriteHeight = pieceTexture.getSize().y / 2;
	float spriteWidth = pieceTexture.getSize().x / 6;
	float spriteY = selectedPiece->white ? 0 : spriteHeight;
	for (int i = 0 ; i < sprites.size() ;i++)
	{
		float spriteX = spriteWidth*(1+i);
		sf::Sprite sprite;
		sprite.setTexture(pieceTexture);
		sprite.setTextureRect(sf::IntRect(spriteX, spriteY, spriteWidth, spriteHeight));
		sprite.setScale(sf::Vector2<float>(0.5, 0.5));
		sprites[i] = sprite;
	}
	SpritePromotion = sprites;
}

void Board::verifyBoardControl()
{
	for (int line = 0; line < boardCells.size(); line++)
	{
		for (int col = 0; col < boardCells[line].size(); col++)
		{
			boardCells[line][col]->defineControl(line, col, &boardCells);
		}
	}
}
