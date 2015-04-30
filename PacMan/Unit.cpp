#include "Unit.h"


CUnit::CUnit(int posX,int posY, char direction, char symb, clock_t period,
	clock_t next,WORD color)
	:direction(direction),symb(symb),period(period),next(next),color(color)
{
	position.X = posX;
	position.Y = posY;
}


bool CUnit::move(Map &map)
{
	if(clock() < next)
		return true;
	next += period;
	switch(direction)
	{
	case 'u':
		{
			if(map(position.X,position.Y - 1) != '#' && map(position.X,position.Y - 1) != '@')
			{
				position.Y--;
				return true;
			}
			break;
		}
	case 'd':
		{
			if(map(position.X ,position.Y + 1) != '#' && map(position.X ,position.Y + 1) != '@')
			{
				position.Y++;
				return true;
			}
			break;
		}
	case 'r':
		{
			if(map(position.X + 1,position.Y) != '#' &&  map(position.X + 1,position.Y) != '@')
			{
				position.X++;
				return true;
			}
			break;
		}
	case 'l':
		{
			if(map(position.X - 1,position.Y) != '#' && map(position.X - 1,position.Y) != '@')
			{
				position.X--;
				return true;
			}
			break;
		}
	}
	return false;
}

char CUnit::getDir()
{
	return direction;
}


COORD CUnit::getPos()
{
	return position;
}

void CUnit::setDir(char chr)
{
	direction = chr;
}


CUnit::~CUnit()
{
}
