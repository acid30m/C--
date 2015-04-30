#pragma once
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <iostream>


using namespace std;

class Map
{	

	char ** map;
	size_t col;
	size_t row;
	COORD start;
public:
	Map();
	void filltest();
	void Show(HANDLE);
	void ReadFromFile(char *,int & score, int & lives);
	void WriteToFile(char *,int score, int lives);
	void setPoint(COORD,char);
	char operator () (int,int);
	~Map(void);
private:

};

