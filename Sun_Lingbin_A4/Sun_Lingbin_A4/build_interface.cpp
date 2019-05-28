#include <iostream>
#include "GL/glui.h"
#include "GL/freeglut.h"
#include "source.h"
#include "build_interface.h"


GLUI *master_glui;
GLUI *glui_contrl;
GLUI *glui_window;
GLUI *glui;
//GLUI *glui_bottom;
GLUI_Checkbox *checkbox;
GLUI_Spinner *spinner;
GLUI_RadioGroup *radio;
GLUI_Panel *panel;
GLUI_EditText *edittext;


void exit_window(int) {
	exit(0);
}

void build_interface(int dis) {
	GLUI_Master.set_glutReshapeFunc(resizeWin);
	GLUI_Master.set_glutMouseFunc(mouse_parsing);
	GLUI_Master.set_glutIdleFunc(myIdle);
	//glui = GLUI_Master.create_glui("Control Windows");
	glui = GLUI_Master.create_glui_subwindow(displayWin, GLUI_SUBWINDOW_BOTTOM);

	GLUI_Panel *panel1 = new GLUI_Panel(glui, "Actions");
	new GLUI_Button(panel1, "Start Over", 0.05, start_over);
	new GLUI_Button(panel1, "Exit", 0.05, exit_window);

}