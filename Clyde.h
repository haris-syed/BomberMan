/*
 * Clyde.h
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */

#ifndef CLYDE_H_
#define CLYDE_H_
#include "Blinky.h"


class Clyde:public Ghost{
public:
	Clyde(int,int,bool);

	void Draw();
};


#endif /* CLYDE_H_ */
