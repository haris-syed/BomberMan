
//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int gamestate;
//enum for displaying menus or playing game ect
enum gameStates {mainmenu, running, pause, endmenu, restartmenu};


// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	b->updateStatus();

	glClearColor(colors[BLUE_VIOLET][0]/*Red Component*/, colors[BLUE_VIOLET][1],	//148.0/255/*Green Component*/,
			colors[BLUE_VIOLET][2]/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	if(gamestate==running && !b->getPacman()->isAlive() && b->getPacman()->getLives() >= 0){
		gamestate=restartmenu;
	}

	else if(gamestate==running && b->getPacman()->isAlive()){

		//draw board
		b->Draw();
		int x, y;

		//b->GetInitPinkyPosition(x, y);
		cout << x << "  y= " << y << endl << flush;
		cout<<12-pixelToIndex(b->getPacman()->getPoint().getY()-25)<<" " <<pixelToIndex(b->getPacman()->getPoint().getX())<<endl;

		//draw pacman at its position

		b->getPacman()->Draw();
		//draw ghosts
		for (int i = 0; i < 4; ++i) {
			if(b->getGhost(i)->isVisible()){
				b->getGhost(i)->Draw();
			}
		}

		//draw text
		b->GetInitTextPosition(x, y);
		DrawString(x, y, "Score = "+Num2Str(b->getPacman()->getScore()), colors[5]);
		DrawString(x+200, y, "Lives: "+Num2Str(b->getPacman()->getLives()), colors[5]);

		//	glPopMatrix();
		if (b->getPacman()->bStatus() == true) {
			x=b->getPacman()->getBombX();
			y=b->getPacman()->getBombY();
			DrawCircle(x,y,10,colors[5]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
		}
	}else if(gamestate==restartmenu){
		DrawString(500, 400, "Restarting", colors[3]);
		b->getPacman()->ressurect();
		gamestate=running;
	}
	else if(gamestate==mainmenu){
		//TODO:Display main menu function
		//displayMenu();
	}
	else if(gamestate==pause){
		//TODO:pause menu
	}


	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	//Pacman *p=dynamic_cast <Pacman*> (d);
	int Y,X;
	Y=b->getPacman()->getPoint().getY();
	X=b->getPacman()->getPoint().getX();

	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		if(Board::getBrick(12-pixelToIndex(Y), pixelToIndex(X-25)) == 0 || Board::getBrick(12-pixelToIndex(Y), pixelToIndex(X-25)) == 4)
			b->getPacman()->moveleft();

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if(Board::getBrick(12-pixelToIndex(Y), pixelToIndex(X-20)+1) == 0 || Board::getBrick(12-pixelToIndex(Y), pixelToIndex(X-20)+1)  == 4)
			b->getPacman()->moveright();

	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		if(Board::getBrick(12-pixelToIndex(Y-25)-1, pixelToIndex(X)) == 0 || Board::getBrick(12-pixelToIndex(Y-25)-1, pixelToIndex(X)) == 4)
			b->getPacman()->moveup();

	}
	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if(Board::getBrick(12-pixelToIndex(Y+25)+1, pixelToIndex(X)) == 0 || Board::getBrick(12-pixelToIndex(Y+25)+1, pixelToIndex(X)) == 4)
			b->getPacman()->movedown();
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	 glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if ((key == 'b' || key == 'B') && !b->getPacman()->bStatus()) //Key for placing the bomb
			{
		b->getPacman()->placeBomb();

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	//TODO:move ghosts here

	if (gamestate==running && b->getPacman()->isAlive()) {
		Point target1(60,0);
		Point target2(60,900);
		Point target3(800,0);
		for (int i = 0; i < 4; ++i) {
			Point targetPacman(pixelToIndex(b->getPacman()->getPoint().getY()),pixelToIndex(b->getPacman()->getPoint().getX()));
			if(b->getGhost(i)->isVisible()){
				Ghost* g=b->getGhost(i);
				if(g->getTime() > 5){
					g->move(targetPacman);
				}
				else if(g->getTime() <= 5){
					switch(i){
					case 0:
						g->move(target1);
						break;
					case 1:
						g->move(target2);
						break;
					case 2:
						g->move(target2);
						break;
					case 3:
						g->move(target3);
						break;
					}
				}
				g->incrementTimer();
			}
		}
	}
	if(b->getPacman()->bStatus())
		b->getPacman()->timeBomb();
	glutPostRedisplay();
	//TODO:bomb time to explode here
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	gamestate=running;
	b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
