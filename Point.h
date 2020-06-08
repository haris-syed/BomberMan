/*
 * Point.h
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#ifndef POINT_H_
#define POINT_H_

class Point{
private:
	int x;
	int y;
public:
	Point(int x,int y):x(x),y(y){}

	Point():x(0),y(0){}

	void setx(int x){
		this->x=x;
	}

	void sety(int y){
		this->y=y;
	}

	int getX() const{
		return x;
	}

	int getY() const{
		return y;
	}

};




#endif /* POINT_H_ */
