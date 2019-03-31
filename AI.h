#ifndef _AI_H_
#define _AI_H_
#include <stdexcept>
#include <string>
#include "BalancedBinarySearchTree.h"
#include "Game.h"

class AI
{
private:
    Game *game;
	BBST<long long, char> mo;
	BBST<long long, char> mx;
	BBST<long long, char> mod;
	BBST<long long, char> mxd;
    BBST_Node<long long,char> *it;
	int choice(long long gam, int time)
    {
		if (time & 1)
			return X_choice(gam, time);
        else
			return O_choice(gam, time);
    }
	int O_choice(long long game, int time)
    {
        long long now = game;
        time++;
        char re = 'X';
		int ret = 0;
		int a = 0, best = -1000;
        int i = 0;
        int j = 0;
		while (i < 50)
        {
			if (!((now >> i) & 3))
            {
				j = i + 2;
				now += ((long long)2 << i);
				while (j < 50)
                {
					if (!((now >> j) & 3))
                    {
						now += ((long long)2 << j);
						a = X_point(now, time);
						if (a > best)
                        {
							if (a == 1000)
								return i / 2 * 25 + j / 2;
                            best = a;
							ret = i / 2 * 25 + j / 2;
							now -= ((long long)2 << j);
                            j+=2;
                            continue;
                        }
						now -= ((long long)2 << j);
						if (!ret)
							ret = i / 2 * 25 + j / 2;
                    }
					j += 2;
                }
				now -= ((long long)2 << i);
            }
			i += 2;
        }

        return ret;
    }
	int X_choice(long long game, int time)
    {
		int ret = 0;
        if(time == 11)
        {
			for (int i = 0; i < 25; i++)
            {
				if (!((game >> i * 2) & 3))
                {
					ret *= 25;
					ret += i;
                }
            }
            return ret;
        }
        time++;
        long long now = game;
		int i = 0, j = 0;
        char re = 'O';
		int a = 0, best = -1000;
		while (i < 50)
        {
			if (!((now >> i) & 3))
            {
				now += ((long long)1 << i);
				j = i + 2;
				while (j < 50)
                {
					if (!((now >> j) & 3))
                    {
						now += ((long long)1 << j);
						a = O_point(game, time);
						if (a > best)
                        {
                            best = a;
							ret = i / 2 * 25 + j / 2;

                        }

						now -= ((long long)1 << j);
						if (!ret)
							ret = i / 2 * 25 + j / 2;
                    }
					j += 2;;
				}
				now -= ((long long)1 << i);
            }
			i += 2;
        }

        return ret;
    }

    char winner(long long game) //¬Ý½ÖÄ¹
    {
		int line = 0;
		int point1 = 0, point2 = 0;
        long long a = 0;

		for (int i = 0; i < 5; i++)
        {
			point1 = 0;
            point2 = 0;
			for (int j = 0; j < 5; j++)
            {
				a = (game >> ((i * 5 + j) * 2));
                if(a & 1)
                    point1--;
				else if (a & 2)
                    point1++;

				a = (game >> (j * 5 + i) * 2);
                if(a & 1)
                    point2--;
				else if (a & 2)
                    point2++;

            }

			if (point1 >= 3)
                line++;
			else if (point1 <= -3)
                line--;

			if (point2 >= 3)
                line++;
			else if (point2 <= -3)
                line--;

        }
		point1 = 0;
        point2 = 0;
		for (int i = 0; i < 5; i++)
        {
			a = (game >> (5 * i + i) * 2);
			if (a & 1)
                point1--;
			else if (a & 2)
                point1++;
			a = (game >> (5 * i + 4 - i) * 2);
            if(a & 1)
                point2--;
			else if (a & 2)
                point2++;
        }
		if (point1 >= 3)
            line++;
		else if (point1 <= -3)
            line --;
		if (point2 >= 3)
            line++;
		else if (point2 <= -3)
            line--;

        if(line > 0)
            return 'O';
        if(line < 0)
            return 'X';
        return '.';
    }
	char O_turn(long long game, int time)
    {
		it = mo.find(game);
		if (it != mo.end())
            return it->item;
        long long now = game;
        time++;
        char re = 'X';
        char a = '\0';
        int i = 0;
        int j = 0;
		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				j = i + 1;
				now += ((long long)2 << (i * 2));
				while (j < 25)
                {
					if (!((now >> j * 2) & 3))
                    {
						now += ((long long)2 << j * 2);
                        if(re == 'X')
                        {
							a = X_turn(now, time);
							if (a == '.')
                            {
								re = '.';
								now -= ((long long)2 << (j * 2));
                                j++;
                                continue;
                            }
                        }
                        else
                        {
							a = X_draw_turn(now, time);
                        }
						if (a == 'O')
                        {
							mo[game] = 'O';
                            return 'O';
                        }

						now -= ((long long)2 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)2 << (i * 2));
            }
            i++;
        }
		mo[game] = re;
        return re;
    }
	char X_turn(long long game, int time)
    {
		it = mx.find(game);
		if (it != mx.end())
            return it->item;
        if(time == 11)
        {
			for (int i = 0; i < 25; i++)
            {
				if (!((game >> i * 2) & 3))
                {
					game += ((long long)1 << i * 2);

                }
            }
			it = mx.find(game);
			if (it != mx.end())
                return it->item;
            char w = winner(game);

            return w;
        }
        time++;
        long long now = game;
		int i = 0, j = 0;
        char re = 'O';
		char a = '\0';
		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				now += ((long long)1 << i * 2);
				j = i + 1;
				while (j < 25)
                {
					if (!(now >> j * 2 & 3))
                    {
						now += ((long long)1 << j * 2);
						if (re == 'O')
                        {
							a = O_turn(now, time);
							if (a == '.')
                                re = '.';
                        }
                        else
						{
							a = O_draw_turn(now, time);
                        }
						if (a == 'X')
                        {
							mx[game] = 'X';
                            return 'X';
						}
						now -= ((long long)1 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)1 << i * 2);
            }
            i++;
        }
		mx[game] = re;
		return re;
    }
	char O_draw_turn(long long game, int time)
    {
        it = mo.find(game);
		if (it != mo.end())
            return it->item;

		if (mod.find(game) != mod.end())
            return '.';
        long long now = game;
        time++;
        char re = 'X';
		char a = '\0';
        int i = 0;
        int j = 0;
		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				j = i + 1;
				now += ((long long)2 << (i * 2));
				while (j < 25)
                {
					if (!((now >> j * 2) & 3))
                    {
						now += ((long long)2 << j * 2);
						a = X_turn(now, time);

						if (a == 'O')
                        {
							mo[game] = 'O';
                            return 'O';
                        }
						else if (a == '.')
                        {
							mod[game] = '.';
                            return '.';
                        }
						now -= ((long long)2 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)2 << (i * 2));
            }
            i++;
        }
		mo[game] = re;
        return re;
    }
	char X_draw_turn(long long game, int time)
    {
		it = mx.find(game);
		if (it != mx.end())
			return it->item;
		if (mxd.find(game) != mxd.end())
            return '.';
		if (time == 11)
        {
			for (int i = 0; i < 25; i++)
            {
				if (!((game >> i * 2) & 3))
                {
					game += (long long)1 << i * 2;
                }
            }
			mx[game] = winner(game);
            return mx[game];
        }
        time++;
        long long now = game;
		int i = 0, j = 0;
        char re = 'O';
		char a = '\0';
		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				now += ((long long)1 << i * 2);
				j = i + 1;
				while (j < 25)
                {
					if (!(now >> j * 2 & 3))
                    {
						now += ((long long)1 << j * 2);
						a = O_turn(now, time);
						if (a == 'X')
                        {
							mx[game] = 'X';
                            return 'X';
                        }
                        else if(a=='.')
                        {
							mxd[game] = '.';
                            return '.';
                        }
						now -= ((long long)1 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)1 << i * 2);
            }
            i++;
        }
		mx[game] = re;
        return re;
    }
	int O_point(long long game, int time)
    {
        long long now = game;
        time++;
        char re = 'X';
		char a = '\0';
		int all = 0, point = 0;
        int i = 0;
        int j = 0;
		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				j = i + 1;
				now += ((long long)2 << (i * 2));
				while (j < 25)
                {
					if (!((now >> j * 2) & 3))
                    {
						now += ((long long)2 << j * 2);
						a = X_turn(now, time);
                        all++;

						if (a == 'O')
                        {
                            point--;
                        }
						else if (a == 'X')
                            point++;
						now -= ((long long)2 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)2 << (i * 2));
            }
            i++;
        }
		mo[game] = re;
		return point * 1000 / all;
    }
	int X_point(long long game, int time)
    {
        if(time == 11)
        {
			for (int i = 0; i < 25; i++)
            {
				if (!((game >> i * 2) & 3))
                {
					game += ((long long)1 << i * 2);
                }
            }

            char w = winner(game);
			if (w == 'X')
                return -1000;
			if (w == 'O')
                return 1000;
            else
                return 0;
        }
        time++;
        long long now = game;
		int i = 0, j = 0;
		char re = 'O';
		char a = '\0';
		int point = 0, all = 0;

		while (i < 25)
        {
			if (!((now >> i * 2) & 3))
            {
				now += ((long long)1 << i * 2);
				j = i + 1;
				while (j < 25)
                {
					if (!(now >> j * 2 & 3))
                    {
						now += ((long long)1 << j * 2);
						a = O_turn(now, time);
						if (a == 'X')
                            point--;
						else if (a == 'O')
                            point++;
                        all++;
						now -= ((long long)1 << j * 2);
                    }
                    j++;
                }
				now -= ((long long)1 << i * 2);
            }
            i++;
        }

		return point * 1000 + all;
    }

public:
    AI(Game *g)
    {
        game = g;
    }
    Button* move()
    {
		int a = 0, b = 0;
		const int prior[9] = { 12,0,6,18,24,4,8,16,21 };
        long long time = 0;

		long long gam = 0;
        int ch = 0;
		int** board = game->getBoard();
        int j = 0;
		for (j = 0; j < 25; j++)
        {
			ch = board[j / 5][j % 5];

            if(ch == 0)
            {
				gam += ((long long)2 << j * 2);
                time++;
            }
            else if(ch == 1)
            {
				gam += ((long long)1 << j * 2);
                time++;
            }
        }
		time /= 2;
		int i = 0;
        if(time == 11)
			throw string("you should call endgame now");

		if (time < 5)
        {
			a = -1;
			b = -1;
			while (i < 9)
            {
				if (!((gam >> (prior[i] * 2)) & 3))
                {
                    a = prior[i];
                    break;
                }
                i++;
            }
            i++;
			while (i < 9)
            {
				if (!((gam >> (prior[i] * 2)) & 3))
                {
                    b = prior[i];
                    break;
                }
                i++;
            }
			if (b == -1)
				b = 1;
			return step_t(2, cordin(a, b));
        }

		a = choice(gam, time);
		return step_t(2, cordin(a / 25, a % 25));
    };
	void endgame(int& a, int& b, int& c)
    {
		int time = 0;
		long long gam = 0;
		int ch = 0, j = 0;

		int** board = game->getBoard();
		for (j = 0; j < 25; j++)
        {
			ch = board[j / 5][j % 5];


			if (ch == 0)
            {
				gam += ((long long)2 << j * 2);
				time++;
            }
			else if (ch == 1)
            {
				gam += ((long long)1 << j * 2);
                time++;
            }
        }
		if (time == 11)
        {
			int i = 0;
			while (i < 25)
            {
				if (!((gam >> i * 2) & 3))
                {
					a = i;
					i++;
                    break;
                }
                i++;
			}
			while (i < 25)
            {
				if (!((gam >> i * 2) & 3))
                {
					b = i;
                    i++;
                    break;
                }
                i++;
            }
			while (i < 25)
            {
				if (!((gam >> i * 2) & 3))
                {
					c = i;
                    i++;
                    break;
                }
                i++;
            }
        }
        else
            throw string("you should call move before the last step");
    }
};
#endif // !_AI_H_
