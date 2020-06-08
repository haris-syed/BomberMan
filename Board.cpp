/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <cstdio>
#include <vector>

//#define WITH_TEXTURES 0

const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };
// defining some utility functions...




#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"Data/solid.png", "Data/brick.png", "Data/brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
  files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		//ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
	delete pacman;
	for (int i = 0; i < ghosts.size(); ++i) {
		delete ghosts.at(i);
	}
	ghosts.clear();

}

void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL : (GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}
	board_array[1][1]=P_DOT;
	board_array[11][15]=P_DOT;
	board_array[1][11]=P_DOT;
	for (int i = 0; i < 4; ++i) {
			ghosts.at(i)->initialiseArray(board_array, BOARD_Y, BOARD_X);
		}

}
//Constructor
Board::Board(int xsize, int ysize) {
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	/*
	 * create pacman
	 */
	int x,y;
	GetInitBombermanPosition(x, y);
	pacman=new Pacman(x,y);
	/*
	 * Create ghosts
	 */
	GetInitPinkyPosition(x, y);
	ghosts.push_back(new Inky(x+60,y,false));
	ghosts.push_back(new Pinky(x,y,true));
	ghosts.push_back(new Blinky(x,y,true));
	ghosts.push_back(new Clyde(x,y-60,false));
//	ghosts.at(1)->changestate();
//	ghosts.at(2)->changestate();

//set up board
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x -10, y, ycellsize, xcellsize,
						colors[SLATE_GRAY]);
				//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
						colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				break;
			case P_DOT:
				DrawCircle(x+20, y+20, 10, colors[GREEN]);
				break;
			}
		}
	}
#endif
	glPopMatrix();
}

Pacman* Board::getPacman() const{
	return pacman;
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}

void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

int Board::getBrick(int r, int c){
	return board_array[r][c];
}

Ghost* Board::getGhost(int i) const{
	if(i < ghosts.size()){
		return ghosts.at(i);
	}else
		return ghosts.at(0);
}
/*
 * recursive function to destroy bricks
 */
void DestroyBricks(int r, int c, int &brickCount){
	if(r > 0 && board_array[r-1][c]==G_BRICK){
		board_array[r-1][c]=NILL;
		brickCount+=1;
	}
	else if(r > 0 && board_array[r-1][c]==R_BRICK){
		DestroyBricks(r-1,c,brickCount);
		board_array[r-1][c]=NILL;
		brickCount++;
	}

	if(r<13 && board_array[r+1][c]==G_BRICK){
		board_array[r+1][c]=NILL;
		brickCount++;
	}
	else if(r<13 && board_array[r+1][c]==R_BRICK){
		DestroyBricks(r+1,c, brickCount);
		board_array[r+1][c]=NILL;
		brickCount++;
	}

	if(c < 16 && board_array[r][c+1]==G_BRICK){
		board_array[r][c+1]=NILL;
		brickCount++;
	}
	else if(c < 16 && board_array[r][c+1]==R_BRICK){
		DestroyBricks(r,c+1, brickCount);
		board_array[r][c+1]=NILL;
		brickCount++;
	}

	if(c>0 && board_array[r][c-1]==G_BRICK){
		board_array[r][c-1]=NILL;
		brickCount++;
	}
	else if(c>0 && board_array[r][c-1]==R_BRICK){
		DestroyBricks(r,c-1, brickCount);
		board_array[r][c-1]=NILL;
		brickCount++;
	}
}


void Board::updateStatus(){
	/*
	 * collision between ghost and pacman
	 */
	int pr,pc,gr,gc;
	pr=12-pixelToIndex(pacman->getPoint().getY());
	pc=pixelToIndex(pacman->getPoint().getX());
	for (int var = 0; var < 4; ++var) {
		if(ghosts.at(var)->isVisible()){//if current ghost is alive
			gr=12-pixelToIndex(ghosts.at(var)->getPoint().getY());
			gc=pixelToIndex(ghosts.at(var)->getPoint().getX());
			if(pr==gr && pc==gc){//collision of ghost and pacman; kill pacman or ghost
				if((ghosts.at(var)->isScared())){//if ghost scared kill ghost
					ghosts.at(var)->kill();
					cout<<"Ghost killed!"<<endl;
					pacman->setScore(pacman->getScore()+200);
				}
				else if(pacman->isAlive()){//else kill pacman
					pacman->kill();
					cout<<"Pacman killed!"<<endl;
					pacman->decrementLives();
					if(pacman->getLives() >= 0){
						int x,y;//reset position if lives left
						GetInitBombermanPosition(x, y);
						pacman->getPoint().setx(x);
						pacman->getPoint().sety(y);
						GetInitPinkyPosition(x, y);
						for (int i = 0; i < 4; ++i) {
							ghosts.at(i)->setPosition(x,y);
						}
					}
				}
			}
		}
	}
	/*
	 * destroy bricks with bomb
	 */
	if (pacman->bStatus() && pacman->bTime() > 4){
		int r,c,b=0;
		pacman->getBombIndex(r, c);
		DestroyBricks(r, c, b);
		pacman->resetbTime();
		cout<<"bricks destroyed: "<<b<<endl;
		pacman->setScore(pacman->getScore()+b*50);
	}
	/*
	 * eat dot
	 */
	if(board_array[12-pixelToIndex(pacman->getPoint().getY())][pixelToIndex(pacman->getPoint().getX())] == P_DOT){
		board_array[12-pixelToIndex(pacman->getPoint().getY())][pixelToIndex(pacman->getPoint().getX())]=0;
		for (int i = 0; i < 4; ++i) {
			ghosts.at(i)->changestate();
		}
	}

}




