/*
 * Character.cpp
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */
#include "Character.h"

Character::Character(int x=0, int y=0):Drawable(x, y),alive(true){}

bool Character::isAlive(){
	return alive;
}

void Character::kill(){
	alive=false;
	visible=false;
}

void Character::ressurect(){
	alive=true;
		visible=true;
}

Character::~Character(){}


