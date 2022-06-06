#ifndef Cell_h
#define Cell_h
//#include "Juicer.h"

class Juicer;

class Cell
{
private:
	int x;
	int y;
	string name;
	Juicer* piece;
public:
	Cell()
	{
		x = 0;
		y = 0;
		name = "a1";
		piece = nullptr;
	}
	Cell(int f, int s, Juicer* p)
	{
		x = f;
		y = s;
		name = "";
		name += ('a' + y);
		name += ('1' + 7 - x);
		piece = p;
	}

	int getX() const
	{
		return x;
	}

	int getY() const
	{
		return y;
	}

	Juicer* getPiece() const
	{
		return piece;
	}

	string getName() const
	{
		return name;
	}

	void setPiece(Juicer* j)
	{
		piece = j;
	}
};
#endif