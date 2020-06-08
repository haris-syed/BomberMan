/*
 * Drawable.h
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include <utility>
#include "Point.h"

class Drawable{
protected:
	Point position;
	bool visible;
public:
	Drawable(int x,int y);

	virtual void Draw()=0;

	Point getPoint();

	bool isVisible();

	void setVisible(bool v);

	void setPosition(int,int);

	virtual ~Drawable();
};



#endif /* DRAWABLE_H_ */
