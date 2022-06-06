#ifndef Knight_h
#define Knight_h

#include "Juicer.h"

class Knight : Juicer
{
public:

	Knight(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "Knight";
		id = 2;
		color = c;
		value = 3;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		if ((abs(x - xto) == 1 && abs(y - yto) == 2) || (abs(x - xto) == 2 && abs(y - yto) == 1))
		{
			return true;
		}
		return false;
	}

};
#endif 