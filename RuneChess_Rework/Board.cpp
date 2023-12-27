#include "Board.h"


Board::~Board()
{
}

Board::Board(int width, int height, sf::RenderWindow* window)
{
	gameWindow = window;
	createBoard(width, height);
	createPieces();
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
	piece = nullptr;
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

void Board::MovePiece(bool* isWhite, float x, float y, Piece* SelectedPiece)
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
				SelectedPiece->pos = sf::Vector2i(col, line);
				SelectedPiece->asMove = true;
				boardCells[line][col]->SetPiece(SelectedPiece);
				SelectedPiece->currentCell->SetPiece(nullptr);
				SelectedPiece->currentCell = boardCells[line][col];
				if (isWhite != nullptr)
				{
					*isWhite = !(*isWhite);
				}
			}
		}
	}
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
			case('Q'):
				spriteX = 1;
				break;
			case('B'):
				spriteX = 2;
				break;
			case('N'):
				piece = new Knight();
				spriteX = 3;
				break;
			case('R'):
				spriteX = 4;
				break;
			case('P'):
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
			if (isupper(c))
			{
				blackPiece.push_back(piece);
			}
			else
			{
				whitePiece.push_back(piece);
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
