/*
 * Ghost.h
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */

#ifndef GHOST_H_
#define GHOST_H_
#include "Pacman.h"
#include "deque"

class Ghost:public Character{
protected:
	int timer;//used to switch between scatter and chase modes
	bool scared;//true when pacman eats a power dot
	int SPEED;
	int array[14][17];
	int scaredTimer;
public:

	Ghost(int,int,bool visible);

	void initialiseArray(const int boardArray[14][17],int,int);

	void clearArray(int r, int c);

	void moveup();

	void movedown();

	void moveleft();

	void moveright();

	void changestate();

	int findDirection(Point,int,int);//uses BFS

	int RandomDirection();//returns a random direction to move

	virtual void move(Point target);//to be called in timer function

	float calculateDistance(int x, int y);

	virtual void Draw()=0;

	void displayArray();

	bool isScared();

	int getTime();

	void incrementTimer();

	void resetTimer();

	~Ghost();


};



#endif /* GHOST_H_ */
