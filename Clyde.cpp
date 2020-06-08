/*
 * Clyde.cpp
 *
 *  Created on: May 8, 2017
 *      Author: syedharis632
 */
#include "Clyde.h"

Clyde::Clyde(int x, int y, bool visible):Ghost(x,y,visible){}

void Clyde::Draw(){
	if(scared==false)
		DrawEnemy(position.getX(), position.getY(), ORANGE, 0.8*60, 0.8*60);
		else
			DrawEnemy(position.getX(), position.getY(), DARK_BLUE, 0.8*60, 0.8*60);
}

