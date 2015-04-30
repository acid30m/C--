#include "PacMan.h"
HANDLE Console = GetStdHandle( STD_OUTPUT_HANDLE );

PacMan::PacMan(void)
	:CUnit(33,11,'d','C', 200,250,FOREGROUND_RED | FOREGROUND_GREEN),lives(3),score(0)
{
}


void PacMan::Show(HANDLE hconsole)
{
	SetConsoleCursorPosition(hconsole,position);
	SetConsoleTextAttribute(
		hconsole,
		FOREGROUND_RED | FOREGROUND_GREEN);
	cout << symb;
}

void PacMan::setPos(int x,int y)
{
	position.X = x;
	position.Y = y;
}

int PacMan::getScore()
{
	return score;
}

int PacMan::getLives()
{
	return lives;
}

void PacMan::setScore(int val)
{
	score = val;
}


void PacMan::setLives(int val)
{
	lives = val;
}


bool PacMan::move(Map & map)
{
	COORD tmp = position;
	if(CUnit::move(map))
	{
		if(map(tmp.X,tmp.Y) == '*')
		{
		++score;
		}
		SetConsoleCursorPosition(Console,tmp);
		cout << ' ';
		map.setPoint(tmp,'_');
		return true;
	}
	return false;
}


PacMan::~PacMan(void)
{
}
