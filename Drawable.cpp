/*
 * Drawable.cpp
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#include "Drawable.h"


Drawable::Drawable(int x, int y){
	position.setx(x);
	position.sety(y);
	visible=true;
}

Point Drawable::getPoint(){
	return position;
}


bool Drawable::isVisible(){
	return visible;
}

void Drawable::setVisible(bool v){
	visible = v;
}

void Drawable::setPosition(int x, int y){
	position.setx(x);
	position.sety(y);
}

Drawable::~Drawable(){}

