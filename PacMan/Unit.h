#pragma once
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "Map.h"


class CUnit
{
protected:
	COORD position;
	char direction;
	char symb;
	clock_t period;
	clock_t next;
	WORD color;
public:
	CUnit(int posX,int posY, char direction, char symb, clock_t period,
		clock_t next,WORD color);
	bool move(Map & map);
	COORD getPos();
	char getDir();
	void setDir(char );
	virtual~CUnit();
};

