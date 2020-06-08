/*
 * Pinky.h
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */

#ifndef PINKY_H_
#define PINKY_H_
#include "Inky.h"


class Pinky:public Ghost{
public:
	Pinky(int,int,bool);

	void move(Point target) override;

	void Draw();

};


#endif /* PINKY_H_ */
