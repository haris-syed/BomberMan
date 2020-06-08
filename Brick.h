/*
 * Brick.h
 *
 *  Created on: May 6, 2017
 *      Author: syedharis632
 */

#ifndef BRICK_H_
#define BRICK_H_
#include "Drawable.h"

class Brick{
private:
	int row, col;//location in array
public:

	Brick(int,int);//takes position

	virtual void destroy();

	int getCol () const;

	void setCol(int);

	int getRow() const;

	void setRow(int);


	virtual ~Brick();


};



#endif /* BRICK_H_ */
