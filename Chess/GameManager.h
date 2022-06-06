#ifndef GameManager_h
#define GameManager_h
#include "Board.h"
#include <iostream>

class GameManager
{
private:
	Board* b;
	RenderWindow* window;
    int selectedx;
    int selectedy;
    bool ended;
    pair<int, int> promotion;

    void draw()
    {
        RectangleShape squares[3];
        squares[0].setSize(Vector2f(70, 70));
        squares[1].setSize(Vector2f(70, 70));
        squares[2].setSize(Vector2f(70, 70));
        squares[0].setFillColor(Color::White);
        squares[1].setFillColor(Color(40, 140, 40));
        squares[2].setFillColor(Color(Color::Yellow));
        int square = 0;
        for (size_t j = 0; j < b->getSize(); j++)
        {
            for (size_t i = 0; i < b->getSize(); i++)
            {
                if (i == selectedy && j == selectedx)
                {
                    squares[2].setPosition(Vector2f(40 + j * 70, 40 + i * 70));
                    window->draw(squares[2]);
                }
                else
                {
                    squares[square].setPosition(Vector2f(40 + j * 70, 40 + i * 70));
                    window->draw(squares[square]);
                }
                if ((*b)[i][j].getPiece() != nullptr)
                {
                    (*b)[i][j].getPiece()->draw(Vector2f(50 + j * 70, 50 + i * 70), window);
                }
                square ^= 1;
            }
            square ^= 1;
        }
    }

public:
	GameManager()
	{
        ended = false;
        promotion = { -1, -1 };
        selectedx = -1;
        selectedy = -1;
		b = new Board();
	    window = new RenderWindow(sf::VideoMode(1000, 640), "Chess!");
	}

    bool AreValidMoves(Juicer::Color c, int en)
    {
        int moves = 0;
        for (size_t j = 0; j < b->getSize(); j++)
        {
            for (size_t i = 0; i < b->getSize(); i++)
            {
                if ((*b)[j][i].getPiece() != nullptr && (*b)[j][i].getPiece()->getColor() == c)
                {
                    for (size_t k = 0; k < b->getSize(); k++)
                    {
                        for (size_t l = 0; l < b->getSize(); l++)
                        {
                            moves += b->fakeMove(j, i, k, l, en);
                        }
                    }
                }
            }
        }
        return moves;
    }

	void start()
	{
        Font f;
        f.loadFromFile("hello-olivia/HelloOlivia.ttf");
        Text t;
        t.setCharacterSize(50);
        t.setPosition(sf::Vector2f(400, 250));
        t.setFillColor(Color(100, 100, 100, 0));
        t.setFont(f);
        Juicer::Color c[2];
        c[0] = Juicer::Color::white;
        c[1] = Juicer::Color::black;
        int turn = 0;
        int enPas = 9;
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == Event::MouseButtonPressed)
                {
                    if (promotion.first != -1)
                    {
                        int x = Mouse::getPosition(*window).x;
                        int y = Mouse::getPosition(*window).y;
                        string a = (c[turn] == Juicer::Color::black ? "white" : "black");
                        if (x >= 100 && x <= 150 && y >= 250 && y <= 300)
                        {
                            (*b)[promotion.first][promotion.second].setPiece((Juicer*)(new Queen(c[turn ^ 1], a + "/queen.png")));
                            promotion = { -1, -1 };
                        }
                        else if (x >= 200 && x <= 250 && y >= 250 && y <= 300)
                        {
                            (*b)[promotion.first][promotion.second].setPiece((Juicer*)(new Rook(c[turn ^ 1], a + "/rook.png")));
                            promotion = { -1, -1 };
                        }
                        else if (x >= 300 && x <= 350 && y >= 250 && y <= 300)
                        {
                            (*b)[promotion.first][promotion.second].setPiece((Juicer*)(new Bishop(c[turn ^ 1], a + "/bishop.png")));
                            promotion = { -1, -1 };
                        }
                        else if (x >= 400 && x <= 450 && y >= 250 && y <= 300)
                        {
                            (*b)[promotion.first][promotion.second].setPiece((Juicer*)(new Knight(c[turn ^ 1], a + "/knight.png")));
                            promotion = { -1, -1 };
                        }
                        else
                        {
                            continue;
                        }
                        if (!AreValidMoves(c[turn], enPas))
                        {
                            if (b->isCheck(c[turn]))
                            {
                                string a = (c[turn] == Juicer::Color::black ? "White " : "Black ");
                                t.setString(a + "won!");
                            }
                            else
                            {
                                t.setString("Draw!");
                            }
                            t.setFillColor(Color::Red);
                            ended = true;
                        }
                    }
                    else if (ended)
                    {
                        ended = false;
                        selectedx = -1;
                        selectedy = -1;
                        b = new Board();
                        turn = 0;
                        enPas = 9;
                        t.setFillColor(Color(100, 100, 100, 0));
                        continue;
                    }
                    int x = Mouse::getPosition(*window).x;
                    int y = Mouse::getPosition(*window).y;
                    x -= 40; y -= 40;
                    if (x <= 560 && y <= 560)
                    {
                        x /= 70;
                        y /= 70;
                        if ((*b)[y][x].getPiece() != nullptr && (*b)[y][x].getPiece()->getColor() == c[turn])
                        {
                            if (x == selectedx && y == selectedy)
                            {
                                selectedx = -1;
                                selectedy = -1;
                            }
                            else
                            {
                                selectedx = x;
                                selectedy = y;
                            }
                        }
                        else if(selectedx == -1)
                        {
                            selectedx = -1;
                            selectedy = -1;
                        }
                        else
                        {
                            int tmp = b->move(selectedy, selectedx, y, x, enPas - 1);
                            if (tmp != 0)
                            {
                                enPas = tmp;
                                turn ^= 1;
                                if ((*b)[y][x].getPiece()->getId() == 1)
                                {
                                    if (y == 0 || y == 7)
                                    {
                                        promotion = { y,x };
                                    }
                                }
                                if (!AreValidMoves(c[turn], enPas))
                                {
                                    if (b->isCheck(c[turn]))
                                    {
                                        string a = (c[turn] == Juicer::Color::black ? "White " : "Black ");
                                        t.setString(a + "won!");
                                    }
                                    else
                                    {
                                        t.setString("Draw!");
                                    }
                                    t.setFillColor(Color::Red);
                                    ended = true;
                                }
                            }
                            selectedx = -1;
                            selectedy = -1;
                        }
                    }
                }
            }
            window->clear(Color(40,40,40));
            draw();
            window->draw(t);
            if (promotion.first != -1)
            {
                string a = (c[turn] == Juicer::Color::black ? "white" : "black");
                auto q = (Juicer*)(new Queen(c[turn^1], a + "/queen.png"));
                auto r = (Juicer*)(new Rook(c[turn^1], a + "/rook.png"));
                auto b = (Juicer*)(new Bishop(c[turn^1], a + "/bishop.png"));
                auto n = (Juicer*)(new Knight(c[turn^1], a + "/knight.png"));
                RectangleShape rs(Vector2f(400, 100));
                rs.setFillColor(Color(40, 200, 40));
                rs.setPosition(Vector2f(75, 225));
                window->draw(rs);
                q->draw(Vector2f(100,250), window);
                r->draw(Vector2f(200,250), window);
                b->draw(Vector2f(300,250), window);
                n->draw(Vector2f(400,250), window);
            }
            window->display();
        }

	}
};


#endif // !GameManager_h
