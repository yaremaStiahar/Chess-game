#ifndef Rook_h
#define Rook_h
#include "Juicer.h"


class Rook : Juicer
{
private:
	bool isMoved;
public:
	
	Rook(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "Rook";
		id = 4;
		color = c;
		value = 5;
		isMoved = false;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		if (x != xto && y != yto)
		{
			return false;
		}
		return true;
	}

	void move()
	{
		isMoved = true;
	}
	bool getIsMoved()
	{
		return isMoved;
	}
};

#endif
