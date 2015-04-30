#include "Ghost.h"
HANDLE Console2 = GetStdHandle( STD_OUTPUT_HANDLE );


Ghost::Ghost(int posX,int posY, char direction, char symb, clock_t period,
	clock_t next,WORD color)
	:CUnit(posX,posY,direction,symb, period,next,color),cond('r')
{
}


void Ghost::SetMode(char chr)
{
	cond = chr;
}


char Ghost::getMode()
{
	return cond;
}

void Ghost::setPos(int x,int y)
{
	position.X = x;
	position.Y = y;
}



void Ghost::move(Map & map,COORD pos)
{
	switch (cond)
	{
	case 'r':
		{
			roarMove(map);
			break;
		}
	case 'p':
		{
			pursuitMove(map,pos);
			break;
		}
	case 's':
		{
			scaryMove(map,pos);
		}
	}
}

bool Ghost::CheckDirection(char dir,Map &map)
{
	switch(dir)
	{
	case 'u':
		{
			if(map(position.X,position.Y - 1) != '#' &&map(position.X,position.Y - 1) != '@')
			return true;
			break;
		}
	case 'd':
		{
			if(map(position.X,position.Y + 1) != '#' &&map(position.X,position.Y + 1) != '@')
			return true;
			break;
		}
	case 'r':
		{
			if(map(position.X + 1,position.Y) != '#' &&map(position.X + 1,position.Y) != '@')
			return true;
			break;
		}
	case 'l':
		{
			if(map(position.X - 1,position.Y) != '#' &&map(position.X - 1,position.Y) != '@')
			return true;
			break;
		}
	}
	return false;
}


void Ghost::roarMove(Map & map)
{
	Corner(map);
	int rnd = rand()%12;
	if((direction != 'u') && (direction != 'd') && (CheckDirection('u',map)) && (rnd < 3))
	{
		direction = 'u';
	}
	else 
		if((direction != 'u') && (direction != 'd') && (CheckDirection('d',map)) && (rnd < 6))
	{
		direction = 'd';
	}
		else 
		if((direction != 'r') && (direction != 'l') && (CheckDirection('r',map)) && (rnd < 9))
	{
		direction = 'r';
	}
			else 
	if((direction != 'r') && (direction != 'l') && (CheckDirection('l',map)) && (rnd < 11))
	{
		direction = 'l';
	}
	if(! CUnit::move(map) )
	{
		ChangeDirection(direction);
		
		roarMove(map);
	}
}


void Ghost::hide(COORD pos, Map & map)
{
	SetConsoleTextAttribute(
		Console2,
		FOREGROUND_BLUE);
	switch(direction)
	{
	case 'u':
		{
			pos.Y++;
			break;
		}
	case 'd':
		{
			pos.Y--;
			break;
		}
	case 'r':
		{
			pos.X--;
			break;
		}
	case 'l':
		{
			pos.X++;
			break;
		}
	}
	if(map(pos.X,pos.Y) == '#' || map(pos.X,pos.Y) == '@')
		return;
	SetConsoleTextAttribute(
		Console2,
		FOREGROUND_RED | FOREGROUND_GREEN);
	SetConsoleCursorPosition(Console2,pos);
	if(map(pos.X,pos.Y) == '_')
		cout << ' ';
	else
	cout << map(pos.X,pos.Y);
}


void Ghost::pursuitMove(Map & map,COORD pacman)
{
	Corner(map);
	int rnd = rand()%12;
	if((direction != 'u') && (direction != 'd') && (CheckDirection('u',map)) && (rnd < 3))
	{
		if(pursuitDir(pacman,position,map) == 'u')
		direction = 'u';
	}
	else 
		if((direction != 'u') && (direction != 'd') && (CheckDirection('d',map)) && (rnd < 6))
	{
		if(pursuitDir(pacman,position,map) == 'u')
		direction = 'd';
	}
		else 
		if((direction != 'r') && (direction != 'l') && (CheckDirection('r',map)) && (rnd < 9))
	{
		if(pursuitDir(pacman,position,map) == 'u')
		direction = 'r';
	}
			else 
		if((direction != 'r') && (direction != 'l') && (CheckDirection('l',map)) && (rnd < 11))
	{
		if(pursuitDir(pacman,position,map) == 'u')
		direction = 'l';
	}
	if(! CUnit::move(map) )
	{
		ChangeDirection(direction);
	}
}

void Ghost::ChangeDirection(char dir)
{
	int tmp = rand()%11;
	switch(direction)
	{
	case 'u':
		(tmp < 5)?  direction = 'r' : direction = 'l';
		break;
	case 'd':
		(tmp < 5)?  direction = 'r' : direction = 'l';
		break;
	case 'l':
		(tmp < 5)? direction = 'u' : direction = 'd';
		break;
	case 'r':
		(tmp < 5)? direction = 'u'  : direction = 'd';
		break;
	}
}

char Ghost::pursuitDir(COORD pacman,COORD ghost, Map & map)
{
	if(pacman.X < ghost.X && pacman.Y > ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'l';
		}
		else if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'd';
		}
	}
	else if(pacman.X < ghost.X && pacman.Y < ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'l';
		}
		else if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'u';
		}
	}
	else if(pacman.X > ghost.X && pacman.Y < ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'r';
		}
		else if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'u';
		}
	}
	else if(pacman.X > ghost.X && pacman.Y > ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'r';
		}
		else if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'd';
		}
	}
	else if(pacman.X > ghost.X && pacman.Y == ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'r';
		}
	}
	else if(pacman.X < ghost.X && pacman.Y == ghost.Y)
	{
		if(direction == 'u' || direction == 'd')
		{
			if(CheckDirection(direction,map))
				return 'l';
		}
	}
	else if(pacman.X == ghost.X && pacman.Y < ghost.Y)
	{
		if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'u';
		}
	}
	else if(pacman.X == ghost.X && pacman.Y > ghost.Y)
	{
		if(direction == 'r' || direction == 'l')
		{
			if(CheckDirection(direction,map))
				return 'd';
		}
	}
}

void Ghost::Corner(Map & map)
{
	switch(direction)
	{
	case 'u':
		{
			if((map(position.X,position.Y - 1) == '#' && map(position.X + 1,position.Y) == '#' && map(position.X - 1,position.Y) == '#') || (map(position.X,position.Y - 1) == '@' && map(position.X + 1,position.Y) == '@' && map(position.X - 1,position.Y) == '@'))
				direction = 'd'; 
			break;
		}
	case 'd':
		{
			if((map(position.X,position.Y + 1) == '#' && map(position.X + 1,position.Y) == '#' && map(position.X - 1,position.Y) == '#') || (map(position.X,position.Y + 1) == '@' && map(position.X + 1,position.Y) == '@' && map(position.X - 1,position.Y) == '@'))
				direction = 'u'; 
			break;
		}
	case 'r':
		{
			if((map(position.X,position.Y + 1) == '#' && map(position.X + 1,position.Y) == '#' && map(position.X,position.Y - 1) == '#') || (map(position.X,position.Y + 1) == '@' && map(position.X + 1,position.Y) == '@' && map(position.X,position.Y - 1) == '@'))
				direction = 'l'; 
			break;
		}
	case 'l':
		{
			if((map(position.X,position.Y + 1) == '#' && map(position.X - 1,position.Y) == '#' && map(position.X,position.Y - 1) == '#') || (map(position.X,position.Y + 1) == '@' && map(position.X - 1,position.Y) == '@' && map(position.X,position.Y - 1) == '@'))
				direction = 'r'; 
			break;
		}
	}
}


void Ghost::scaryMove(Map & map,COORD pacman)
{
	Corner(map);
	int rnd = rand()%12;
	if((direction != 'u') && (direction != 'd') && (CheckDirection('u',map)) && (rnd < 3))
	{
		direction = 'u';
	}
	else 
		if((direction != 'u') && (direction != 'd') && (CheckDirection('d',map)) && (rnd < 6))
	{
		direction = 'd';
	}
		else 
		if((direction != 'r') && (direction != 'l') && (CheckDirection('r',map)) && (rnd < 9))
	{
		direction = 'r';
	}
			else 
	if((direction != 'r') && (direction != 'l') && (CheckDirection('l',map)) && (rnd < 11))
	{
		direction = 'l';
	}
	if(! CUnit::move(map) )
	{
		ChangeDirection(direction);
		
		scaryMove(map,pacman);
	}		
}

void Ghost::Show(Map & map)
{
	hide(position,map);
	SetConsoleCursorPosition(Console2,position);
	if(cond == 's')
	{
		SetConsoleTextAttribute(
		Console2,
		FOREGROUND_BLUE);
	}
	else
	{
	SetConsoleTextAttribute(
		Console2,
		color);
	}
	cout << symb;
}

Ghost::~Ghost(void)
{
}
