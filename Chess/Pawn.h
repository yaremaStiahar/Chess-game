#ifndef Pawn_h
#define Pawn_h
#include "Juicer.h"


class Pawn : Juicer
{
private:
	bool isMoved;


public:

	Pawn(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "Pawn";
		id = 1;
		color = c;
		value = 1;
		isMoved = false;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		int up = color == Color::black ? 1 : -1;
		if (abs(x - xto) == 1 && y + up == yto)
		{
			return true;
		}
		if (x != xto)
		{
			return false;
		}
		if (y + up == yto || (!isMoved && y + 2 * up == yto))
		{
			return true;
		}
		return false;
	}

	void move()
	{
		isMoved = true;
	}
};
#endif