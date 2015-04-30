#pragma once
#include "Unit.h"
class PacMan :public CUnit
{
	 int score;
	 int lives;
public:
	

	PacMan(void);
	void Show(HANDLE);
	bool move(Map &);
	void start();
	int getScore();
	int getLives();
	void setScore(int);
	void setLives(int);
	void setPos(int,int);
	
	~PacMan(void);
};

