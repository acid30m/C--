#include "Map.h"
#include <fstream>


Map::Map()
	:col(70),row(20)
{
	start.X = 0;
	start.Y = 0;
	map = new char*[row];
	for(size_t i = 0;i < 20;i++)
	{
		map[i] = new char[col];
	}
}


void Map::filltest()
{
	int cntr = 47;
	for(size_t i = 0;i < row;i++)
	{
		for(size_t j = 0;j < col;j++)
		{
			map[i][j] = cntr;

		}
		cntr++;
	}
}

void Map::Show(HANDLE hConsole)
{
	for(size_t i = 0;i < row;i++)
	{
		for(size_t j = 0;j < col;j++)
		{
			SetConsoleCursorPosition(hConsole,start);
			if(map[i][j] == '_')
				cout << ' ';
			else
			{
				if(map[i][j] == '*' || map[i][j] == 'O')
					SetConsoleTextAttribute(
					hConsole,FOREGROUND_RED | FOREGROUND_GREEN);
				else
					SetConsoleTextAttribute(
					hConsole,
					FOREGROUND_BLUE);
				cout << map[i][j];
			}
			start.X++;
		}
		start.X = 0;
		start.Y++;
	}
	start.X = 0;
	start.Y = 0;
	cout << endl;
}

void Map::WriteToFile(char * filename,int score, int lives)
{
	ofstream fout;
	fout.open(filename);
	if(fout == NULL)
	{
		cerr << "Error writing in file";
	}
	else
	{
		for(size_t i = 0;i < row;i++)
		{
			for(size_t j = 0;j < col;j++)
			{
				fout << map[i][j];

			}
			fout << "\n";
		}
		fout << score << "\n";
		fout << lives << "\n";
		fout.close();
		cout << "Writing succesfully" << endl;
	}
}





void Map::ReadFromFile(char * filename,int & score, int & lives)
{
	ifstream fin;
	fin.open(filename);
	if(fin == NULL)
	{
		cerr << "Error reading file";
	}
	else
	{

		for(size_t i = 0;i < row;i++)
		{
			for(size_t j = 0;j < col;j++)
			{
				fin >> map[i][j];
			}			
		}
		fin >> score;
		fin >> lives;
	}

}


char Map::operator () (int x,int y)
{
	return this-> map[y][x];
}

void Map::setPoint(COORD pos, char chr)
{
	map[pos.Y][pos.X] = chr;
}


Map::~Map(void)
{

}
