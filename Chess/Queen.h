#ifndef Queen_h
#define Queen_h
#include "Juicer.h"

class Queen : Juicer
{
public:

	Queen(Color c, string filepath)
	{
		t.loadFromFile(filepath);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 50, 50));
		name = "Queen";
		id = 5;
		color = c;
		value = 9;
	}

	bool checkIfCanMove(int x, int y, int xto, int yto) override
	{
		if (abs(x - xto) == abs(y - yto))
		{
			return true;
		}
		if (x == xto || y == yto)
		{
			return true;
		}
		return false;
	}

};
#endif
//wihtout Freddie Mercury T.T  