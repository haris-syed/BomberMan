/*
 * Brick.cpp
 *
 *  Created on: May 6, 2017
 *      Author: syedharis632
 */
#include "Brick.h"

Brick::Brick(int x, int y){
	setRow(x);
	setCol(y);
}
int Brick::getCol() const {
		return col;
	}

	void Brick::setCol(int col) {
		this->col = col;
	}

	int Brick::getRow() const {
		return row;
	}

	void Brick::setRow(int row) {
		this->row = row;
	}
void Brick::destroy(){}

void draw(){}


