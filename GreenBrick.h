/*
 * GreenBrick.h
 *
 *  Created on: May 6, 2017
 *      Author: syedharis632
 */

#ifndef GREENBRICK_H_
#define GREENBRICK_H_

class GreenBrick:public Brick{

public:
	GreenBrick(int,int);

	void destroy() override;

};



#endif /* GREENBRICK_H_ */
