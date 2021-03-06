// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "GL/freeglut.h"
#include "GL/glui.h"
#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
#include "source.h"
#include <algorithm>
#include "build_interface.h"
#include "init.h"


using namespace std;

int displayWin, winSizeX, winSizeY;

GLfloat unit_width;
GLfloat unit_height;

p_pieces select_square;
int select_index;

int n_y;
GLfloat old_pt[2];



void resizeWin(int w, int h) { ; }

void myIdle() { ; }

int click_count;

GLfloat o_lu_x;
GLfloat o_lu_y;
GLfloat o_ru_x;
GLfloat o_ru_y;
GLfloat o_rd_x;
GLfloat o_rd_y;
GLfloat o_ld_x;
GLfloat o_ld_y;
GLfloat o_ct_x;
GLfloat o_ct_y;

GLfloat n_lu_x;
GLfloat n_lu_y;
GLfloat n_ru_x;
GLfloat n_ru_y;
GLfloat n_rd_x;
GLfloat n_rd_y;
GLfloat n_ld_x;
GLfloat n_ld_y;
GLfloat n_ct_x;
GLfloat n_ct_y;

void rotate_color(p_color *cl_array) {
	p_color temp = cl_array[0];
	cl_array[0] = cl_array[1];
	cl_array[1] = cl_array[2];
	cl_array[2] = cl_array[3];
	cl_array[3] = temp;
	
}

void draw_square(p_pieces piece) {
	glBegin(GL_POLYGON);
	glColor3f(piece.s1().r(), piece.s1().g(), piece.s1().b());
	glVertex2f(piece.lu().x(), piece.lu().y());
	glVertex2f(piece.ct().x(), piece.ct().y());
	glVertex2f(piece.ru().x(), piece.ru().y());
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(piece.s2().r(), piece.s2().g(), piece.s2().b());
	glVertex2f(piece.ru().x(), piece.ru().y());
	glVertex2f(piece.ct().x(), piece.ct().y());
	glVertex2f(piece.rd().x(), piece.rd().y());
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(piece.s3().r(), piece.s3().g(), piece.s3().b());
	glVertex2f(piece.rd().x(), piece.rd().y());
	glVertex2f(piece.ct().x(), piece.ct().y());
	glVertex2f(piece.ld().x(), piece.ld().y());
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(piece.s4().r(), piece.s4().g(), piece.s4().b());
	glVertex2f(piece.ld().x(), piece.ld().y());
	glVertex2f(piece.ct().x(), piece.ct().y());
	glVertex2f(piece.lu().x(), piece.lu().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.lu().x(), piece.lu().y());
	glVertex2f(piece.rd().x(), piece.rd().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.ru().x(), piece.ru().y());
	glVertex2f(piece.ld().x(), piece.ld().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.lu().x(), piece.lu().y());
	glVertex2f(piece.ld().x(), piece.ld().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.lu().x(), piece.lu().y());
	glVertex2f(piece.ru().x(), piece.ru().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.ru().x(), piece.ru().y());
	glVertex2f(piece.rd().x(), piece.rd().y());
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(piece.ld().x(), piece.ld().y());
	glVertex2f(piece.rd().x(), piece.rd().y());
	glEnd();

	glFlush();
}

void draw_pieces() {
	for (int i = 0; i < 24; i++) {
		draw_square(to_move[i]);
	}
}

void draw_layour() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			draw_square(to_go[i][j]);
		}
	}
}

void draw_graphs() {

	// Area Saving puzzles
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(unit_width, (winSizeY - unit_height));
	glVertex2f((5 * unit_width), (winSizeY - unit_height));
	glVertex2f((5 * unit_width), (winSizeY - (7 * unit_height)));
	glVertex2f(unit_width, (winSizeY - (7 * unit_height)));
	glEnd();

	// Area Saving Results
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f((6 * unit_width), (winSizeY - (2 * unit_height)));
	glVertex2f((12 * unit_width), (winSizeY - (2 * unit_height)));
	glVertex2f((12 * unit_width), (winSizeY - (6 * unit_height)));
	glVertex2f((6 * unit_width), (winSizeY - (6 * unit_height)));
	glEnd();
	
	draw_pieces();
}

void print_list(vector<p_pieces> list) {
	for (vector<p_pieces>::iterator it = list.begin(); it != list.end(); it++) {
		cout << "lu pos: (" << it->lu().x() << ", " << it->lu().y() << ")" << endl;
		cout << "ru pos: (" << it->ru().x() << ", " << it->ru().y() << ")" << endl;
		cout << "rd pos: (" << it->rd().x() << ", " << it->rd().y() << ")" << endl;
		cout << "ld pos: (" << it->ld().x() << ", " << it->ld().y() << ")" << endl;
		cout << endl;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winSizeX, 0, winSizeY);
	//glViewport(0, 0, 600, 600);
	glMatrixMode(GL_MODELVIEW);
	//glViewport(-300, -200, 1200, 800);
	draw_graphs();

	glutSwapBuffers();
}

void start_over(int) {
	cout << "start over" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	click_count = 0;
	select_index = 0;
	o_lu_x = 0; o_lu_y = 0;
	o_ru_x = 0; o_ru_y = 0;
	o_rd_x = 0; o_rd_y = 0;
	o_ld_x = 0; o_ld_y = 0;
	o_ct_x = 0; o_ct_y = 0;

	n_lu_x = 0; n_lu_y = 0;
	n_ru_x = 0; n_ru_y = 0;
	n_rd_x = 0; n_rd_y = 0;
	n_ld_x = 0; n_ld_y = 0;
	n_ct_x = 0; n_ct_y = 0;
	p_list.clear();
	fill_pieces(unit_width, (winSizeY - unit_height), unit_width, unit_height);
	to_move[24];
	copy_array(p_list, to_move);

	init_switch();
	//display();
	//glutPostRedisplay();
	glutSwapBuffers();
}

int find_index(int x, int y) {
	int n_y = 7 - y - 1;
	return (n_y * 4) + x;
}

void mouse_moving(int x, int y) {
//	if (x >= unit_width && x <= 5 * unit_width
//		&& n_y >= unit_height && n_y <= 7 * unit_height) {
		n_y = winSizeY - y;

		GLfloat dx = x - old_pt[0];
		GLfloat dy = n_y - old_pt[1];

		cout << "dx: " << dx << endl;
		cout << "dy: " << dy << endl;
		cout << endl;

		n_lu_x = to_move[select_index - 1].lu().x() + dx;
		n_lu_y = to_move[select_index - 1].lu().y() + dy;
		n_ru_x = to_move[select_index - 1].ru().x() + dx;
		n_ru_y = to_move[select_index - 1].ru().y() + dy;
		n_rd_x = to_move[select_index - 1].rd().x() + dx;
		n_rd_y = to_move[select_index - 1].rd().y() + dy;
		n_ld_x = to_move[select_index - 1].ld().x() + dx;
		n_ld_y = to_move[select_index - 1].ld().y() + dy;
		n_ct_x = to_move[select_index - 1].ct().x() + dx;
		n_ct_y = to_move[select_index - 1].ct().y() + dy;

		p_pieces cur_piece = to_move[select_index - 1];

		point nw_pts[5];
		point lu(n_lu_x, n_lu_y);
		point ru(n_ru_x, n_ru_y);
		point rd(n_rd_x, n_rd_y);
		point ld(n_ld_x, n_ld_y);
		point ct(n_ct_x, n_ct_y);
		nw_pts[0] = lu;
		nw_pts[1] = ru;
		nw_pts[2] = rd;
		nw_pts[3] = ld;
		nw_pts[4] = ct;

		p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
		p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
		p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
		p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
		p_color nw_cls[4];
		nw_cls[0] = col1;
		nw_cls[1] = col2;
		nw_cls[2] = col3;
		nw_cls[3] = col4;
		to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);

		old_pt[0] = x;
		old_pt[1] = n_y;
//	}
	glutPostRedisplay();
}

void mouse_parsing(int button, int state, int x, int y) {
	n_y = winSizeY - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		old_pt[0] = x;
		old_pt[1] = n_y;

		int temp_x = x / 100;
		int temp_y = n_y / 100;
		select_index = find_index(temp_x, temp_y);

		cout << "cur sqr:" << select_index << endl;

//		if (x >= 1 * unit_width
//			&& x <= 5 * unit_width
//			&& n_y >= 1 * unit_height
//			&& n_y <= 7 * unit_height) {
			o_lu_x = to_move[select_index - 1].lu().x();
			o_lu_y = to_move[select_index - 1].lu().y();
			o_ru_x = to_move[select_index - 1].ru().x();
			o_ru_y = to_move[select_index - 1].ru().y();
			o_rd_x = to_move[select_index - 1].rd().x();
			o_rd_y = to_move[select_index - 1].rd().y();
			o_ld_x = to_move[select_index - 1].ld().x();
			o_ld_y = to_move[select_index - 1].ld().y();
			o_ct_x = to_move[select_index - 1].ct().x();
			o_ct_y = to_move[select_index - 1].ct().y();
			//		}	

			p_pieces cur_piece = to_move[select_index - 1];
			point nw_pts[5];
			point lu(cur_piece.lu().x(), cur_piece.lu().y());
			point ru(cur_piece.ru().x(), cur_piece.ru().y());
			point rd(cur_piece.rd().x(), cur_piece.rd().y());
			point ld(cur_piece.ld().x(), cur_piece.ld().y());
			point ct(cur_piece.ct().x(), cur_piece.ct().y());
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color temp_cls[4];
			temp_cls[0] = col1;
			temp_cls[1] = col2;
			temp_cls[2] = col3;
			temp_cls[3] = col4;
			if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
				rotate_color(temp_cls);
			}
			to_move[select_index - 1] = p_pieces(nw_pts, temp_cls);
			click_count++;
			cout << "click count:" << click_count << endl;
		//}
	}
	else {
		click_count = 0;
		p_pieces cur_piece = to_move[select_index - 1];
		int i = cur_piece.ct().x() / unit_width;
		int j = cur_piece.ct().y() / unit_height;
		int m = i - 6;
		int n = j - 2;
		// in black area
		if (to_move[select_index - 1].ct().x() < 6 * unit_width
			|| to_move[select_index - 1].ct().x() > 12 * unit_width
			|| to_move[select_index - 1].ct().y() < 2 * unit_height
			|| to_move[select_index - 1].ct().y() > 6 * unit_height) {

			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);

			
		}
		// one piece on the current position
		else if (p_switch[m][n] == FALSE) {
			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);
		}
		// the color on the bounder does not match
		else if ((n + 1 < 4)
			&& !p_switch[m][n + 1]
			&& !compare(to_go[m][n + 1].s3(), p_color(0, 0, 0))
			&& !compare(cur_piece.s1(), to_go[m][n + 1].s3())
			) {
			cout << "up not same" << endl;
			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);
		}
		else if ((n - 1 >= 0) 
			&& !p_switch[m][n - 1]
			&& !compare(to_go[m][n - 1].s1(), p_color(0, 0, 0))
			&& !compare(cur_piece.s3(), to_go[m][n - 1].s1())) {
			cout << "down not same" << endl;
			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);
		}
		else if ((m - 1 >= 0)
			&& !p_switch[m - 1][n]
			&& !compare(to_go[m - 1][n].s2(), p_color(0, 0, 0))
			&& !compare(cur_piece.s4(), to_go[m - 1][n].s2())) {
			cout << "left not same" << endl;
			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);
		 }
		else if ((m + 1 < 6)
			&& !p_switch[m + 1][n]
			&& !compare(to_go[m + 1][n].s4(), p_color(0, 0, 0))
			&& !compare(cur_piece.s2(), to_go[m + 1][n].s4())) {
			cout << "right not same" << endl;
			point nw_pts[5];
			point lu(o_lu_x, o_lu_y);
			point ru(o_ru_x, o_ru_y);
			point rd(o_rd_x, o_rd_y);
			point ld(o_ld_x, o_ld_y);
			point ct(o_ct_x, o_ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color nw_cls[4];
			nw_cls[0] = col1;
			nw_cls[1] = col2;
			nw_cls[2] = col3;
			nw_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, nw_cls);
		 }
		else {
			// the original place is empty

			// the square come to to_go
			//p_pieces cur_piece = to_move[select_index - 1];
			cout << "cur i: " << i << endl;
			cout << "cur j: " << j << endl;

			GLfloat ld_x = i * unit_width;
			GLfloat ld_y = j * unit_height;
			GLfloat rd_x = (i + 1) * unit_width;
			GLfloat rd_y = j * unit_height;
			GLfloat lu_x = i * unit_width;
			GLfloat lu_y = (j + 1) * unit_height;
			GLfloat ru_x = (i + 1) * unit_width;
			GLfloat ru_y = (j + 1) * unit_height;
			GLfloat ct_x = i * unit_width + (unit_width / 2);
			GLfloat ct_y = j * unit_height + (unit_height / 2);

			point nw_pts[5];
			point lu(lu_x, lu_y);
			point ru(ru_x, ru_y);
			point rd(rd_x, rd_y);
			point ld(ld_x, ld_y);
			point ct(ct_x, ct_y);
			nw_pts[0] = lu;
			nw_pts[1] = ru;
			nw_pts[2] = rd;
			nw_pts[3] = ld;
			nw_pts[4] = ct;

			p_color col1(cur_piece.s1().r(), cur_piece.s1().g(), cur_piece.s1().b());
			p_color col2(cur_piece.s2().r(), cur_piece.s2().g(), cur_piece.s2().b());
			p_color col3(cur_piece.s3().r(), cur_piece.s3().g(), cur_piece.s3().b());
			p_color col4(cur_piece.s4().r(), cur_piece.s4().g(), cur_piece.s4().b());
			p_color temp_cls[4];
			temp_cls[0] = col1;
			temp_cls[1] = col2;
			temp_cls[2] = col3;
			temp_cls[3] = col4;

			to_move[select_index - 1] = p_pieces(nw_pts, temp_cls);

			to_go[i - 6][j - 2] = p_pieces(nw_pts, temp_cls);
			p_switch[m][n] = FALSE;
		}
	}
	//glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(250, 100);

	winSizeX = 1300;
	winSizeY = 800;
	glutInitWindowSize(winSizeX, winSizeY);

	unit_width = (float)winSizeX / (float)13.0;
	unit_height = (float)winSizeY / (float)8.0;
	fill_pieces(unit_width, (winSizeY - unit_height), unit_width, unit_height);
	copy(p_list.begin(), p_list.end(), to_move);
	//init_goal(unit_width, (winSizeY - unit_height), unit_width, unit_height);
	init_switch();
	displayWin = glutCreateWindow("Assignment 4");

	click_count = 0;
	glutDisplayFunc(display);
	build_interface(displayWin);
	glutMouseFunc(mouse_parsing);
	glutMotionFunc(mouse_moving);
	//glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu