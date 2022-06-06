#ifndef Juicer_h
#define Juicer_h
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


class Juicer
{
public:
	enum class Color
	{
		white,
		black
	};

	int getId() const
	{
		return id;
	}

	Color getColor() const
	{
		return color;
	}

	string getName() const
	{
		return name;
	}

	void setName(const string& n)
	{
		name = n;
	}

	void setColor(const Color& c)
	{
		color = c;
	}

	void setId(const int& i)
	{
		id = i;
	}

	virtual bool checkIfCanMove(int x, int y, int xto, int yto) = 0;

	void draw(Vector2f v, RenderWindow* window)
	{
		s.setPosition(v);
		window->draw(s);
	}

protected:
	string name;
	int id;
	Color color;
	int value;
	Sprite s;
	Texture t;

};
#endif