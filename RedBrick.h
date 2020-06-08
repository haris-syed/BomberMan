/*
 * RedBrick.h
 *
 *  Created on: May 6, 2017
 *      Author: syedharis632
 */

#ifndef REDBRICK_H_
#define REDBRICK_H_

class RedBrick:public Brick{
public:

	RedBrick(int,int);

	void destroy() override;

};




#endif /* REDBRICK_H_ */
