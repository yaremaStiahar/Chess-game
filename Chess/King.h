#ifndef King_h
#define King_h
#include "Juicer.h"

class King : Juicer
{
private:
	bool isMoved;
public:

	King(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "King";
		id = 6;
		color = c;
		value = 0;
		isMoved = false;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		if (abs(x - xto) <= 1 && abs(y - yto) <= 1)
		{
			return true;
		}
		if (abs(x - xto) == 2 && abs(y - yto) == 0 && !isMoved && y == (color == Color::white ? 7 : 0))
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