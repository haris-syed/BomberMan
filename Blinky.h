/*
 * Blinky.h
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */

#ifndef BLINKY_H_
#define BLINKY_H_
#include "Pinky.h"


class Blinky:public Ghost{
public:
	Blinky(int,int,bool);

	void Draw();
};


#endif /* BLINKY_H_ */
