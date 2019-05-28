#include "GL/glut.h"
#include "GL/glui.h"
#include <iostream>


using namespace std;

extern int displayWin, winSizeX, winSizeY;

void resizeWin(int w, int h);
void mouse_parsing(int, int, int, int);
void myIdle();
