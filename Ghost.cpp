/*
 * Ghost.cpp
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */
#include "Ghost.h"

Ghost::Ghost(int x, int y, bool visible):Character(x, y),timer(0),scared(false),SPEED(60){
	setVisible(visible);
}


void Ghost::initialiseArray(const int boardArray[14][17],int rows=14, int cols=17){
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if(boardArray[i][j]==1 || boardArray[i][j]==2 || boardArray[i][j]==3)//if brick then mark as -1
				array[i][j]=-1;
			else
				array[i][j]=0;
		}
	}
}

void Ghost::clearArray(int r, int c){
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if(array[i][j]!= -1){
				array[i][j]=0;
			}
		}
	}
}

void Ghost::displayArray(){
	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 17; ++j) {
			cout<< array[i][j]<<" " ;
		}
		cout<<endl;
	}
	cout<<endl;
}

void Ghost::changestate(){
	if(scared==true){
		scared=false;
	}else
		scared=true;
}

bool Ghost::isScared(){
	return scared;
}

int Ghost::RandomDirection(){
	srand((int)time(0));
	return rand()%4+1;
}

float Ghost::calculateDistance(int x,int y){
	return sqrt(x*x + y*y);
}

int Ghost::findDirection( Point target,int rows=14, int cols=16){
	int r,c;//position of ghost in array
	r=12-pixelToIndex(this->position.getY());
	c=pixelToIndex(this->position.getX());
	float shortestDistance=0.0;
	Point shortestPoint(0,0);
	//copy array to use in search
	array[r][c]=5;//ghost
	//add neighbors of ghost to queue
	shortestDistance=calculateDistance(r-target.getX(),c-target.getY());
	shortestPoint.setx(r);shortestPoint.sety(c);
	deque <Point> queue;
	Point p(0,0);
	if (r > 0 && r < rows && array[r-1][c]==0){//top index
		p.setx(r-1); p.sety(c);
		queue.push_back(p);
		array[r-1][c]=1;
	}
	if(r >=0 && r < rows-1 && array[r+1][c]==0){//bottom index
		p.setx(r+1); p.sety(c);
		queue.push_back(p);
		array[r+1][c]=2;
	}
	if ( c > 0 && c < cols && array[r][c-1]==0){//left
		p.setx(r); p.sety(c-1);
		queue.push_back(p);
		array[r][c-1]=3;
	}
	if(c >=0 && c < cols-1 && array[r][c+1]==0){//right
		p.setx(r); p.sety(c+1);
		queue.push_back(p);
		array[r][c+1]=4;
	}

	float distance;
	while(!queue.empty()){
		p=queue.at(0);
		queue.pop_front();
		r=p.getX();
		c=p.getY();
		distance=calculateDistance(r-target.getX(), c-target.getY());
		//update distance and point
		if(distance < shortestDistance){
			shortestDistance=distance;
			shortestPoint.setx(r);shortestPoint.sety(c);
		}
		//add neighbors
		if (r > 0 && r < rows && array[r-1][c]==0){//top index
			p.setx(r-1); p.sety(c);
			queue.push_back(p);
			array[r-1][c]=array[r][c];
		}
		if(r >=0 && r < rows-1 && array[r+1][c]==0){//bottom index
			p.setx(r+1); p.sety(c);
			queue.push_back(p);
			array[r+1][c]=array[r][c];
		}
		if ( c > 0 && c < cols && array[r][c-1]==0){//left
			p.setx(r); p.sety(c-1);
			queue.push_back(p);
			array[r][c-1]=array[r][c];
		}
		if(c >=0 && c < cols-1 && array[r][c+1]==0){//right
			p.setx(r); p.sety(c+1);
			queue.push_back(p);
			array[r][c+1]=array[r][c];
		}
	}
	return array[shortestPoint.getX()][shortestPoint.getY()];

}
void Ghost::moveup(){
	position.sety(position.getY()+SPEED);
}

void Ghost::movedown(){
	position.sety(position.getY()-SPEED);
}

void Ghost::moveleft(){
	position.setx(position.getX()-SPEED);
}

void Ghost::moveright(){
	position.setx(position.getX()+SPEED);
}

void Ghost::move(Point target){

	int direction=findDirection(target,14,17);
	cout<<"Move called direction:"<<direction<<"r:"<<pixelToIndex(this->position.getY())<<"c:"<<pixelToIndex(this->position.getX())<<endl;
	switch (direction){
		case 1:
			moveup();
			break;
		case 2:
			movedown();
			break;
		case 3:
			moveleft();
			break;
		case 4:
			moveright();
			break;
		}
	clearArray(14, 17);
}

int Ghost::getTime(){
	return timer;
}

void Ghost::incrementTimer(){
	timer+=1;
	if(timer>=10){
		resetTimer();
	}
}

void Ghost::resetTimer(){
	timer=0;
}
Ghost::~Ghost(){}



