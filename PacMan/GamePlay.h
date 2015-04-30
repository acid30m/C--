#pragma once
#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"

class GamePlay
{
	PacMan patagonist;
	Ghost Blinky;
	Ghost Pinky;
	Ghost Inky;
	Ghost Clyde;
	Map map;
	clock_t period;
	clock_t next;
public:
	GamePlay();
	void play();
	void isEnergy( Map & map, COORD pacman);
	void chMode();
	void isTime();
	void isPinky();
	void isInky();
	void isClyde();
	void isGhost();
	bool isEnd();
	bool chkPos(COORD pos1,COORD pos2);
private:
	void reset();
	void freeGhost();
};