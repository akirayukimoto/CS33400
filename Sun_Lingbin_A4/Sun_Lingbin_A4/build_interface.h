#pragma once
#include <iostream>
#include "GL/freeglut.h"
#include "GL/glui.h"

extern GLUI *glui;
extern GLUI *glui_left;
extern GLUI *glui_bottom;
extern GLUI_Checkbox *checkbox;
extern GLUI_Spinner *spinner;
extern GLUI_RadioGroup *radio;
extern GLUI_Panel *panel;
extern GLUI_EditText *edittext;

void start_over(int);

void build_interface(int dis);