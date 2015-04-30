#pragma once
#include "Unit.h"
class Ghost :public CUnit
{
	char cond;
public:
	Ghost(int posX,int posY, char direction, char symb, clock_t period,
		clock_t next,WORD color);
	void move(Map &,COORD);
	void SetMode(char );
	~Ghost(void);
	void Show(Map & map);
	char getMode();
	void setPos(int,int);
private:
	void ChangeDirection(char dir);
	bool CheckDirection(char dir,Map &map);
	void roarMove(Map &);
	void pursuitMove(Map &,COORD);
	void hide(COORD,Map &);
	char pursuitDir(COORD pacman,COORD ghost,Map & map);
	void Corner(Map &);
	void scaryMove(Map & map,COORD pacman);
};

