/*
 * Pacman.h
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#ifndef PACMAN_H_
#define PACMAN_H_
#include "Character.h"
#include "util.h"


class Pacman:public Character{
private:
	int sprite;
	int spritetimer;
	int score;
	const int SPEED;
	int lives;
	int bombTimer;
	bool bombStatus;
	Point bombPosition;
public:

	Pacman(int,int);

	void Draw();

	void moveup();

	void movedown();

	void moveright();

	void moveleft();

	int getScore();

	void setScore(int);

	int getLives();

	void decrementLives();

	void eatdot();

	void eatpowerdot();

	void timeBomb();

	void placeBomb();

	bool bStatus();

	int bTime();

	void resetbTime();

	void getBombIndex(int& r, int&c);

	int getBombX(){
		return bombPosition.getX();
	}

	int getBombY(){
		return bombPosition.getY();
	}



};



#endif /* PACMAN_H_ */
