//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Evpoly.h"
#include "freeglut.h"
#include "evaluate_all.h"
#include "findCurve.h"

using namespace std;
/*
char text[] =
//"x";
//"10*x-y";
"y^2-x^3-x^2";
*/

//char text[200];
const char *text;
static int n_value = 10;
bool is_eval = TRUE;
//int window_id;

double pos_x = -2.0;
double pos_y = -2.0;

double p1_x = -2.0;
double p1_y = -2.0;

double points_array[2][2];
int num_points = 0;

int width = 600;
int height = 600;

int button_kind = -1;

static void menu_callback(int menu) {
	std::cout << "Menu Item " << menu << " was clicked" << std::endl;
	if (menu == 0) {
		std::cout << "Select GRID N" << std::endl;
		std::cout << "Please input your N Value: ";
		std::cin >> n_value;
		//cout << "The input N value is: " << n_value << endl;
	}

	if (n_value != 0) {
		//cout << "n value = " << n_value << endl;
	}
}

// TODO: Draw x and y axises
static void draw_coordinate() {

	//double prev_x = 0;
	//double prev_y = 0;

	double x;
	double y;
	for (int i = 0; i <= n_value; i++) {
		x = ((double)i) / (double)n_value;
		for (int j = 0; j <= n_value; j++) {
			y = ((double)j) / (double)n_value;
			glBegin(GL_LINES);
			glColor3d(1, 1, 1);
			glVertex2d(x, y);
			glVertex2d(-x, y);
			glVertex2d(x, -y);
			glVertex2d(-x, -y);
			glVertex2d(y, x);
			glVertex2d(y, -x);
			glVertex2d(-y, x);
			glVertex2d(-y, -x);
			glEnd();
		}
	}


	glBegin(GL_LINES);
	glLineWidth(5.0f);
	glColor3f(0, 1, 1);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(5.0f);
	glColor3f(0, 1, 1);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();

} /* draw_coordinate */


static void display() {
	if (button_kind == 0) {
		glPointSize(10);
		glBegin(GL_POINTS);
		if (num_points == 0) {
			glColor3f(0.5f, 0, 0.5f);
		}
		else {
			glColor3f(0.3f, 0.5f, 0.0f);
		}
		glVertex2d(pos_x, pos_y);
		glEnd();
	}
	glutSwapBuffers();
	//glutPostRedisplay();
}

static void evaluate_graph(int value, const char *input_text) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_coordinate();
	evaluate_graph_first(value, input_text);
	glutSwapBuffers();
}

static void find_curve(int value, const char *input_text) {
	//mouse_chasing();
	if (input_text != NULL || input_text[0] != 0) {
		pExp *func;
		double r1;
		double r2;
		func = readExp(_strdup(text));
		r1 = func->eval(p1_x, p1_y);
		r2 = func->eval(points_array[1][0], points_array[1][1]);
		if ((r1 > 0 && r2 > 0) ||
			(r1 < 0 && r2 < 0)) {
			cout << "r1: " << r1 << endl;
			cout << "r2: " << r2 << endl;
			num_points = 0;
		}
		else {
			finding_curve(value, points_array[0][0], points_array[0][1],
				points_array[1][0], points_array[1][1], input_text);
			points_array[0][0] = 0;
			points_array[0][1] = 0;
			points_array[1][0] = 0;
			points_array[1][1] = 0;
			input_text= { 0 };
		}
	}
	glutSwapBuffers();
}

static void drawing_graph(int value, const char *input_text) {
	if (input_text != NULL && input_text[0] != 0) {
		if (is_eval == TRUE) {
			evaluate_graph(value, input_text);
		}
		else {
			if (num_points == 2) {
				find_curve(value, input_text);
			}
		}
	}
}

// TODO: Menu "Other Actions"
static void other_actions(int menu_id) {
	switch (menu_id)
	{
	case 0:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		num_points = 0;
		glLoadIdentity();
		std::cout << "Clear Window" << std::endl;
		draw_coordinate();
		glutSwapBuffers();
		break;
	case 1:
		glutPostRedisplay();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		std::cout << "Refresh Window" << std::endl;
		draw_coordinate();
		if (text != NULL && text[0] != 0) {
			drawing_graph(n_value, text);
		}
		glutSwapBuffers();
		break;
	case 2:
		glutDestroyWindow(glutGetWindow());
		std::cout << "Exit Program" << std::endl;
		exit(0);
		break;
	default:
		break;
	}
} /* other_actions */

static void sample_callback(int menu_id) {

	switch (menu_id)
	{
	case 0:
		text = "x^2+y^2-0.8";
		break;
	case 1:
		text = "x^2+4*y^2-0.5";
		break;
	case 2:
		text = "x^2-4*y^2-0.09";
		break;
	case 3:
		text = "y^2-x^3";
		break;
	case 4:
		text = "y^2-x^2-x^3";
		break;
	case 5:
		text = "y^2-x^4-y^4";
		break;
	case 6:
		text = "y^2-x^6-y^6";
		break;
	case 7:
		text = "(x^2+y^2)^2-(x^2-y^2)";
		break;
	case 8:
		text = "8*x^4-6*1.1*x^2*y+1.21*y^2-4*1.331*y^3+4*1.21*1.21*y^4";
		break;
	case 9:
		text = "x^4+y2^*(x^2-x+1)*1.44-2*y*x^2*1.2";
		break;
	case 10:
		text = "(x^2+y^2)^2+3*x^2*y-y^3";
		break;
	case 11:
		text = "(x^2+y^2)^3-4*x^2*y^2";
		break;
	}
	cout << "exp: " << text << endl;
	cout << "grind n: " << n_value << endl;

	drawing_graph(n_value, text);
}

static void input_function(int menu_id) {
	switch (menu_id)
	{
	case 0:
		char str[200];
		cout << "Input your own function: ";
		cin >> str;
		text = str;
		drawing_graph(n_value, text);
		break;
	default:
		break;
	}
}

static void mode_selection(int menu_id) {
	switch (menu_id)
	{
	case 0:
		is_eval = TRUE;
		break;
	case 1:
		is_eval = FALSE;
		break;
	default:
		break;
	}
}


static void input_points(double x, double y) {
	if (num_points < 2) {
		points_array[num_points][0] = x;
		points_array[num_points][1] = y;
		num_points++;
	}
	else {
		points_array[1][0] = x;
		points_array[1][1] = y;
	}
	p1_x = points_array[0][0];
	p1_y = points_array[0][1];
	cout << "num_points: " << num_points << endl;
	cout << "point 1: (" << points_array[0][0] << ", " << points_array[0][1] << ")" << endl;
	cout << "point 2: (" << points_array[1][0] << ", " << points_array[1][1] << ")" << endl;
	if (num_points == 2 && is_eval == FALSE) {
		if (text != NULL && text[0] != 0) {
			drawing_graph(n_value, text);
		}
	}
}

// TODO: Create Main Menu with their sub menus
static void create_menu() {
	// create menu

	cout << "input n: " << n_value << endl;

	// sub entry of other_action
	int sub_menu_id_other = glutCreateMenu(other_actions);
	glutAddMenuEntry("CLEAR", 0);
	glutAddMenuEntry("REFRESH", 1);
	glutAddMenuEntry("EXIT", 2);

	// sub entries of evaluation
	int sub_menu_id_eval = glutCreateMenu(mode_selection);
	glutAddMenuEntry("EVALUATE ALL", 0);
	glutAddMenuEntry("FIND CURVE", 1);

	// sub entries of poly_sample
	int sub_menu_id_sample = glutCreateMenu(sample_callback);
	glutAddMenuEntry("CIRCLE", 0);
	glutAddMenuEntry("ELLIPSE", 1);
	glutAddMenuEntry("HYPERBOLA", 2);
	glutAddMenuEntry("SEMICUBIC PARABOLA", 3);
	glutAddMenuEntry("ALPHA CURVE", 4);
	glutAddMenuEntry("TOUCHING TACNODE", 5);
	glutAddMenuEntry("CROSSING TACNODE", 6);
	glutAddMenuEntry("LEMNISCATE", 7);
	glutAddMenuEntry("RABBIT EARS", 8);
	glutAddMenuEntry("CURVED LOBE", 9);
	glutAddMenuEntry("TREFOIL", 10);
	glutAddMenuEntry("CLOVER LEAF", 11);

	// sub entries of polynomial
	int sub_menu_id_poly = glutCreateMenu(input_function);
	glutAddMenuEntry("READ POLYNOMIAL", 0);
	glutAddSubMenu("POLYNOMIAL SAMPLE", sub_menu_id_sample);

	// root menu
	int menu_id = glutCreateMenu(menu_callback);
	glutAddSubMenu("OTHER ACTION", sub_menu_id_other);
	glutAddSubMenu("EVALUATE", sub_menu_id_eval);
	glutAddMenuEntry("GRID N [0,1]", 0);
	glutAddSubMenu("POLYNOMIAL", sub_menu_id_poly);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

} /* create_menu */


static void mouse_press(int button, int state, int x, int y) {
	button_kind = button;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		cout << "clicked!" << endl;
		
		pos_x = (double)(x - width/2) / (double)(width/2);
		pos_y = (double)(height/2 - y) / (double)(height/2);
		cout << "current pos: (" << pos_x << ", " << pos_y << ")" << endl;
		if (is_eval == FALSE) {
			input_points(pos_x, pos_y);
		}
	}
}

static void change_size(int width_len, int height_len) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width_len, height_len);
	double ratio = (double)width_len / (double)height_len;
	if (width_len != height_len) {
		gluOrtho2D(-15.0, 15.0, -15.0 / ratio, 15.0 / ratio);
	}
	else {
		gluOrtho2D(-15.0*ratio, 15.0*ratio, -15.0, 15.0);
	}
	width = width_len;
	height = height_len;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_coordinate();
	if (text != NULL && text[0] != 0) {
		drawing_graph(n_value, text);
	}

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	// initialize the window
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(30, 30);

	// create window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Evaluating Polynomial");

	glutReshapeFunc(change_size);

	// set empty display function
	glutDisplayFunc(display);

	// draw xy axes
	glLoadIdentity();
	draw_coordinate();

	// create menu
	create_menu();
	//cout << "input n: " << n_value << endl;

	// set mouse callbacks
	glutMouseFunc(mouse_press);


	glutMainLoop();

	return 0;
}
