#ifndef Bishop_h
#define Bishop_h
#include "Juicer.h"

class Bishop : Juicer
{
public:

	Bishop(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "Bishop";
		id = 3;
		color = c;
		value = 3;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		if (abs(x - xto) != abs(y - yto))
		{
			return false;
		}
		return true;
	}

};
#endif