/*
 * Character.h
 *
 *  Created on: May 1, 2017
 *      Author: syedharis632
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Drawable.h"

class Character:public Drawable{
private:
	bool alive;

public:
	Character(int,int);

	virtual void Draw()=0;

	bool isAlive();

	void kill();

	void ressurect();

	virtual ~Character();
};



#endif /* CHARACTER_H_ */
