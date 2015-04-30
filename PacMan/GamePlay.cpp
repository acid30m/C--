#include "GamePlay.h"
#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"

#define SCROLL_UP 'w'
#define SCROLL_DOWN 's'
#define SCROLL_RIGHT 'd'
#define SCROLL_LEFT 'a'

HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );



GamePlay::GamePlay()
	:patagonist(), Blinky(29,5,'l','W', 260,280,FOREGROUND_RED), 
	Pinky(29,5,'l','W', 255,260,FOREGROUND_BLUE | FOREGROUND_GREEN),
	Inky(29,5,'l','W', 240,290,FOREGROUND_RED | FOREGROUND_GREEN), 
	Clyde(29,5,'l','W', 220,270,FOREGROUND_RED | FOREGROUND_BLUE),
	period(10000), next(0)
{
}

void GamePlay::play()
{
	srand(time(0));
	char tmp2;
	cout << "New game - enter \'n\'" << endl;
	cout << "Resume game - enter \'r\'" << endl;
	cin >> tmp2;
	int score, lives;
	if(tmp2 == 'n')
		map.ReadFromFile("map.txt",score,lives);
	if(tmp2 == 'r')
	{
		map.ReadFromFile("saved.txt",score,lives);
		patagonist.setScore(score);
		patagonist.setLives(lives);
	}
	map.Show(hConsole);
	COORD tmp;
	char chr;
	do{
		do{
			if(isEnd())
			{
				char choice;
				cout << "Want to play again? (y/n)" << endl;
				cin >> choice;
				if(choice == 'n')
				{
					cout << "Bye!" << endl;
					exit(EXIT_SUCCESS);
				}
				else if(choice == 'y')
				{
					Sleep(800);
					reset();
				}
			}
			Blinky.move(map,patagonist.getPos());
			Pinky.move(map,patagonist.getPos());
			Inky.move(map,patagonist.getPos());
			Clyde.move(map,patagonist.getPos());
			if(patagonist.move(map))
			{
				patagonist.Show(hConsole);
			}
			isTime();
			isGhost();
			isEnergy(map, patagonist.getPos());
			Blinky.Show(map);
			Pinky.Show(map);
			Inky.Show(map);
			Clyde.Show(map);
			patagonist.Show(hConsole);
			tmp.X = 1;
			tmp.Y = 22;
			SetConsoleCursorPosition(hConsole,tmp);
			cout << "Score : " << patagonist.getScore() << endl;
			tmp.Y++;
			SetConsoleCursorPosition(hConsole,tmp);
			cout << "Lives : " <<  patagonist.getLives() << endl;
		} while ( !kbhit() );
		chr = getch();
		if( chr == -32 )
			chr = getch();

		switch(chr)
		{
		case SCROLL_UP:
			patagonist.setDir('u');			
			break;
		case SCROLL_DOWN:
			patagonist.setDir('d');
			break;
		case SCROLL_RIGHT:
			patagonist.setDir('r');
			break;
		case SCROLL_LEFT:
			patagonist.setDir('l');
			break;
		case 'p':
			{
				system("cls");
				cout << "Paused" << endl;
				cout << "Resume - press \'r\'" << endl;
				cout << "Save state and exit - press \'s\'" << endl;
				cin >> tmp2;
				if(tmp2 == 's')
				{
					map.WriteToFile("saved.txt",patagonist.getScore(),patagonist.getLives());
					exit(0);
				}
				map.Show(hConsole);
			}
			break;
		}




	}while ( chr != 27 );
	map.Show(hConsole);
}


void GamePlay::isEnergy( Map & map, COORD pacman)
{
	if(map(pacman.X,pacman.Y) == 'O')
	{
		Blinky.SetMode('s');
		Pinky.SetMode('s');
		Inky.SetMode('s');
		Clyde.SetMode('s');
		next += 5 * 280;
	}
}

void GamePlay::isTime()
{
	if(clock() > next)
	{
		next += period;
		switch(Blinky.getMode())
		{
		case 's':
			{
				Blinky.SetMode('p');
				Pinky.SetMode('p');
				Inky.SetMode('p');
				Clyde.SetMode('p');
			}
			break;
		case 'p':
			{
				Blinky.SetMode('r');
				Pinky.SetMode('r');
				Inky.SetMode('r');
				Clyde.SetMode('r');
			}
			break;
		case 'r':
			{
				Blinky.SetMode('p');
				Pinky.SetMode('p');
				Inky.SetMode('p');
				Clyde.SetMode('p');
			}
			break;
		}
		freeGhost();
	}
	else return;
}

void GamePlay::isGhost()
{
	if( chkPos(patagonist.getPos(),Blinky.getPos()) )
	{
		if(Blinky.getMode() == 's')
		{
			Blinky.setPos(29,5);
		}
		else
		{
			patagonist.setLives(patagonist.getLives() - 1);
			Sleep(500);
			map.Show(hConsole);
		}
	}
	if( chkPos(patagonist.getPos(),Pinky.getPos()) )
	{
		if(Pinky.getMode() == 's')
		{
			Pinky.setPos(29,5);
		}
		else
		{
			patagonist.setLives(patagonist.getLives() - 1);
			Sleep(500);
			map.Show(hConsole);
		}
	}
	if( chkPos(patagonist.getPos(),Inky.getPos()) )
	{
		if(Inky.getMode() == 's')
		{
			Inky.setPos(29,5);

		}
		else
		{
			patagonist.setLives(patagonist.getLives() - 1);
			Sleep(500);
			map.Show(hConsole);
		}
	}
	if( chkPos(patagonist.getPos(),Clyde.getPos()) )
	{
		if(Clyde.getMode() == 's')
		{
			Clyde.setPos(29,5);
		}
		else
		{
			patagonist.setLives(patagonist.getLives() - 1);
			Sleep(500);
			map.Show(hConsole);
		}
	}


}

bool GamePlay::chkPos(COORD pos1,COORD pos2)
{
	if(pos1.X == pos2.X && pos1.Y == pos2.Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool GamePlay::isEnd()
{
	if(patagonist.getLives() <= 0)
	{
		system("cls");
		cout << "GAME OVER" << endl;
		cout << "YOU LOSE!" << endl;
		return true;
	}
	else if(patagonist.getScore() == 212)
	{
		system("cls");
		cout << "GAME OVER" << endl;
		cout << "YOU WIN!" << endl;
		return true;
	}
	return false;
}

void GamePlay::reset()
{
	int ignore;
	Blinky.setPos(27,3);
	Pinky.setPos(23,3);
	Inky.setPos(30,3);
	Clyde.setPos(25,3);
	patagonist.setPos(33,11);
	patagonist.setLives(3);
	patagonist.setScore(0);
	map.ReadFromFile("map.txt",ignore,ignore);
	system("cls");
	map.Show(hConsole);
}


void GamePlay::freeGhost()
{
	if(Blinky.getPos().X > 27 && Blinky.getPos().X < 35 && Blinky.getPos().Y > 3 && Blinky.getPos().Y < 7)
	{
		Blinky.setPos(27,3);
		return;
	}
	else if(Pinky.getPos().X > 27 && Pinky.getPos().X < 35 && Pinky.getPos().Y > 3 && Pinky.getPos().Y < 7)
	{
		Pinky.setPos(27,3);
		return;
	}
	else if(Inky.getPos().X > 27 && Inky.getPos().X < 35 && Inky.getPos().Y > 3 && Inky.getPos().Y < 7)
	{
		Inky.setPos(27,3);
		return;
	}
	else if(Clyde.getPos().X > 27 && Clyde.getPos().X < 35 && Clyde.getPos().Y > 3 && Clyde.getPos().Y < 7)
	{
		Clyde.setPos(27,3);
		return;
	}
}