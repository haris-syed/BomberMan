/*
 * Pinky.cpp
 *
 *  Created on: May 8, 2017
 *      Author: syedharis632
 */
#include "Pinky.h"


Pinky::Pinky(int x, int y, bool visible):Ghost(x,y,visible){}

void Pinky::Draw(){
	if(scared==false)
	DrawEnemy(position.getX(), position.getY(), PINK, 0.8*60, 0.8*60);
	else
		DrawEnemy(position.getX(), position.getY(), DARK_BLUE, 0.8*60, 0.8*60);
}

void Pinky::move(Point target){
	int direction=RandomDirection();
	int r, c;
	r=12-pixelToIndex(position.getY());
	c=pixelToIndex(position.getX());
	switch (direction){
	case 1:
		if (r > 0 && array[r-1][c]==0)
			moveup();
		break;
	case 2:
		if(r >=0 && r < 13 && array[r+1][c]==0)
			movedown();
		break;
	case 3:
		if ( c > 0 && array[r][c-1]==0)
			moveleft();
		break;
	case 4:
		if(c >=0 && c < 15 && array[r][c+1]==0)
			moveright();
		break;
	}
}
