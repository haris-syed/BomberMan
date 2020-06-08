/*
 * Pacman.cpp
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#include "Pacman.h"

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

void DrawBomberMan2(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/) {
	DrawCircle(sx, sy, radius, colors[YELLOW]);
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
				radius / 10, colors[BLACK]);
}




Pacman::Pacman(int x, int y):Character(x, y) ,SPEED(5), score(0), sprite(1) ,spritetimer(0),lives(3){}

void Pacman::Draw(){
	if(spritetimer<=4 && sprite==1){
		DrawBomberman(position.getX(), position.getY(), 25, YELLOW);
		spritetimer+=2;
		if(spritetimer>4){
			sprite=2;
			spritetimer=8;
		}
	}
	else if(spritetimer>=4 && sprite==2){
		DrawBomberMan2(position.getX(), position.getY(), 25, YELLOW);
		spritetimer-=2;
		if(spritetimer < 4){
			sprite=1;
			spritetimer=0;
		}
	}
}

void Pacman::moveup(){
	/*if( (BoardParts) b->getAt (getX()/60-1, getY()/60) == NILL ){
		position.sety(getY()-SPEED);
	}*/
	position.sety(position.getY()+SPEED);
}

void Pacman::movedown(){
	position.sety(position.getY()-SPEED);
}

void Pacman::moveleft(){
	position.setx(position.getX()-SPEED);
}

void Pacman::moveright(){
	position.setx(position.getX()+SPEED);
}

int Pacman::getScore(){
	return score;
}

void Pacman::setScore(int s){
	score=s;
}
int Pacman::getLives(){
	return lives;
}

void Pacman::decrementLives(){
	lives-=1;
}

void Pacman::timeBomb(){
	bombTimer+=1;
}

void Pacman::placeBomb(){
	bombStatus=true;
	bombPosition.setx(position.getX());
	bombPosition.sety(position.getY());
	bombTimer=0;
}

bool Pacman::bStatus(){
	return bombStatus;
}

int Pacman::bTime(){
	return bombTimer;
}

void Pacman::resetbTime(){
	bombTimer=0;
	bombStatus=false;
}
void Pacman::getBombIndex(int& r, int&c){
	r=12-pixelToIndex(bombPosition.getY());
	c=pixelToIndex(bombPosition.getX());
}

