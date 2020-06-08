/*
 * Inky.h
 *
 *  Created on: May 7, 2017
 *      Author: syedharis632
 */

#ifndef INKY_H_
#define INKY_H_
#include "Ghost.h"

class Inky:public Ghost{
public:
	Inky(int,int,bool);

	void Draw();

};



#endif /* INKY_H_ */
