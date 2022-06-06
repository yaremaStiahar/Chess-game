#ifndef Board_h
#define Board_h
#include "Juicer.h"
#include "Cell.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Board
{
private:
	const int size = 8;
	vector<vector<Cell>> board;
public:
	Board()
	{
		board = vector<vector<Cell>>(size, vector<Cell>(size));
		vector<string> setup(8);
		ifstream in("Setup.txt");
		for (size_t i = 0; i < size; i++)
		{
			in >> setup[i];
		}
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				switch (setup[i][j])
				{
				case '*':
					board[i][j] = Cell(i, j, nullptr);
					break;
				case 'p':
					board[i][j] = Cell(i, j, (Juicer*)(new Pawn(Juicer::Color::black, "black/pawn.png")));
					break;
				case 'r':
					board[i][j] = Cell(i, j, (Juicer*)(new Rook(Juicer::Color::black, "black/rook.png")));
					break;
				case 'n':
					board[i][j] = Cell(i, j, (Juicer*)(new Knight(Juicer::Color::black, "black/knight.png")));
					break;
				case 'b':
					board[i][j] = Cell(i, j, (Juicer*)(new Bishop(Juicer::Color::black, "black/bishop.png")));
					break;
				case 'q':
					board[i][j] = Cell(i, j, (Juicer*)(new Queen(Juicer::Color::black, "black/queen.png")));
					break;
				case 'k':
					board[i][j] = Cell(i, j, (Juicer*)(new King(Juicer::Color::black, "black/king.png")));
					break;


				case 'P':
					board[i][j] = Cell(i, j, (Juicer*)(new Pawn(Juicer::Color::white, "white/pawn.png")));
					break;
				case 'R':
					board[i][j] = Cell(i, j, (Juicer*)(new Rook(Juicer::Color::white, "white/rook.png")));
					break;
				case 'N':
					board[i][j] = Cell(i, j, (Juicer*)(new Knight(Juicer::Color::white, "white/knight.png")));
					break;
				case 'B':
					board[i][j] = Cell(i, j, (Juicer*)(new Bishop(Juicer::Color::white, "white/bishop.png")));
					break;
				case 'Q':
					board[i][j] = Cell(i, j, (Juicer*)(new Queen(Juicer::Color::white, "white/queen.png")));
					break;
				case 'K':
					board[i][j] = Cell(i, j, (Juicer*)(new King(Juicer::Color::white, "white/king.png")));
					break;

				default:
					break;
				}
			}
		}
	}

	const int getSize() const
	{
		return size;
	}

	vector<Cell>& operator [](int y)
	{
		return board[y];
	}

	bool isCheck(Juicer::Color color)
	{
		int x = -1, y = -1;
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getId() == 6 && color == board[i][j].getPiece()->getColor())
				{
					x = j;
					y = i;
					break;
				}
			}
			if (x != -1)
				break;
		}
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (canMove(i, j, x, y, false))
				{
					return true;
				}
			}
		}
		return false;
	}

	int canMove(int x, int y, int xTo, int yTo, int enPassant)
	{
		int ret = 1;
		Juicer* p = board[y][x].getPiece();
		if (x == xTo && y == yTo)
		{
			return 0;
		}
		else if (p == nullptr)
		{
			return 0;
		}
		else if (!p->checkIfCanMove(x, y, xTo, yTo))
		{
			return 0;
		}
		else if (board[yTo][xTo].getPiece() != nullptr && board[yTo][xTo].getPiece()->getColor() == p->getColor())
		{
			return 0;
		}
		else if (p->getId() == 1)//pawn
		{
			int up = p->getColor() == Juicer::Color::black ? 1 : -1;
			if (abs(x - xTo) == 1)
			{
				if (xTo == enPassant && yTo == (p->getColor() == Juicer::Color::black ? 5 : 2))
				{
					ret = 4;
				}
				else if (board[yTo][xTo].getPiece() != nullptr)
				{
					ret = 1;
				}
				else
				{
					ret = 0;
				}
			}
			else if (abs(y - yTo) == 2)
			{
				if (board[yTo][xTo].getPiece() != nullptr || board[(yTo+y)/2][xTo].getPiece() != nullptr)
				{
					return 0;
				}
			}
			if (x==xTo && board[yTo][xTo].getPiece() != nullptr)
			{
				return 0;
			}
		}
		else if (p->getId() == 3 || p->getId() == 4 || p->getId() == 5)
		{
			int xup = xTo > x ? 1 : x == xTo ? 0 : -1;
			int yup = yTo > y ? 1 : y == yTo ? 0 : -1;
			for (int i = 1; i < max(abs(x - xTo), abs(y - yTo)); i++)
			{
				if (board[y + i * yup][x + i * xup].getPiece() != nullptr)
				{
					return 0;
				}
			}
		}
		else if (p->getId() == 6)
		{
			if (abs(x - xTo) == 2)
			{
				if (isCheck(p->getColor()))
				{
					return 0;
				}
				Juicer* r = board[y][xTo > x ? 7 : 0].getPiece();
				if (r == nullptr || r->getId() != 4)
				{
					return 0;
				}
				Rook* rook = reinterpret_cast<Rook*>(r);
				if (rook->getIsMoved())
				{
					return 0;
				}
				int m = xTo > x ? 1 : -1;
				for (size_t i = 1; i < 3; i++)
				{
					if (board[yTo][x + i * m].getPiece() == nullptr)
					{
						board[yTo][x + i * m].setPiece(p);
						if (isCheck(p->getColor()))
						{
							board[yTo][x + i * m].setPiece(nullptr);
							return 0;
						}
						board[yTo][x + i * m].setPiece(nullptr);
					}
					else
						return 0;
				}
				return 2 + int(xTo < x);
			}
			return 1;
		}
		else if (p->getId() == 2)
		{
			ret = 1;
		}
		return ret;
	}

	int fakeMove(int x, int y, int xTo, int yTo, int enPassant)
	{
		Juicer* p = board[x][y].getPiece();
		int val = canMove(y, x, yTo, xTo, enPassant);
		if (val == 0)
		{
			return 0;
		}
		Juicer* cp = board[xTo][yTo].getPiece();
		board[x][y].setPiece(nullptr);
		board[xTo][yTo].setPiece(p);
		if (isCheck(p->getColor()))
		{
			board[x][y].setPiece(p);
			board[xTo][yTo].setPiece(cp);
			return 0;
		}
		board[x][y].setPiece(p);
		board[xTo][yTo].setPiece(cp);
		return 1;
	}

	int move(int x, int y, int xTo, int yTo, int enPassant)
	{
		Juicer* p = board[x][y].getPiece();
		int val = canMove(y, x, yTo, xTo, enPassant);
		if (val == 0)
		{
			return 0;
		}
		Juicer* cp = board[xTo][yTo].getPiece();
		board[x][y].setPiece(nullptr);
		board[xTo][yTo].setPiece(p);
		if (isCheck(p->getColor()))
		{
			board[x][y].setPiece(p);
			board[xTo][yTo].setPiece(cp);
			return 0;
		}
		if (p->getId() == 1)
		{
			Pawn* pa = reinterpret_cast<Pawn*>(p);
			pa->move();
		}
		if (p->getId() == 4)
		{
			Rook* pa = reinterpret_cast<Rook*>(p);
			pa->move();
		}
		if (p->getId() == 6)
		{
			King* pa = reinterpret_cast<King*>(p);
			pa->move();
		}
		if (val == 2)
		{
			Rook* pa = reinterpret_cast<Rook*>(board[x][7].getPiece());
			pa->move();
			board[x][7].setPiece(nullptr);
			board[x][5].setPiece((Juicer*)pa);
		}
		if (val == 3)
		{
			Rook* pa = reinterpret_cast<Rook*>(board[x][0].getPiece());
			pa->move();
			board[x][0].setPiece(nullptr);
			board[x][3].setPiece((Juicer*)pa);
		}
		if (val == 4)
		{
			int enp = p->getColor() == Juicer::Color::black ? 4 : 3;
			board[enp][enPassant].setPiece(nullptr);
		}
		if (p->getId() == 1 && abs(xTo-x)==2)
		{
			return y + 1;
		}
		return 9;
	}

};
#endif