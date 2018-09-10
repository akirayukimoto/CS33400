#include "evaluate_all.h"

using namespace std;

void draw_condition(double x, double y, int value, const char *text) {
	double unit;
	unit = 1.0 / (double)value;
	double x1;
	double x2;
	double x3;
	double y1;
	double y2;
	double y3;

	x1 = x;
	x2 = x + unit;
	x3 = x + unit;
	y1 = y + unit;
	y2 = y + unit;
	y3 = y;

	pExp *func;
	double r0 = 0;
	double r1 = 0;
	double r2 = 0;
	double r3 = 0;
	char *cur_exp = _strdup(text);
	func = readExp(cur_exp);
	r0 = func->eval(x, y);
	r1 = func->eval(x1, y1);
	r2 = func->eval(x2, y2);
	r3 = func->eval(x3, y3);

	double p1_x = -2.0;
	double p1_y = -2.0;
	double p2_x = -2.0;
	double p2_y = -2.0;
	double temp1;
	double temp2;


	if (r0 > 0) {
		// 1. r1, r2, r3 are -
		if (r1 <= 0 && r2 <= 0 && r3 <= 0) {
			p1_y = y;
			p2_x = x;

			temp1 = (double)r0 / (double)(fabs(r3) + r0);
			temp2 = (double)r0 / (double)(fabs(r1) + r0);

			p1_x = x + ((double)temp1 * (double)unit);
			p2_y = y + ((double)temp2 * (double)unit);
		}
		// 2. r2, r3 are -
		else if (r2 <= 0 && r3 <= 0 && r1 >= 0) {
			p1_y = y;
			p2_y = y1;

			temp1 = (double)r0 / (double)(r0 + fabs(r3));
			temp2 = (double)r1 / (double)(r1 + fabs(r2));

			p1_x = x + ((double)temp1 * (double)unit);
			p2_x = x1 + ((double)temp2 * (double)unit);
		}
		// 3. r1, r2 are -
		else if (r1 <= 0 && r2 <= 0 && r3 >= 0) {
			p1_x = x;
			p2_x = x3;

			temp1 = (double)r0 / (double)(r0 + fabs(r1));
			temp2 = (double)r3 / (double)(r3 + fabs(r2));

			p1_y = y + ((double)temp1 * (double)unit);
			p2_y = y3 + ((double)temp2 * (double)unit);
		}
		// 4. r1, r3 are -
		else if (r1 <= 0 && r3 <= 0 && r2 >= 0) {
			double p3_x;
			double p3_y;
			double p4_x;
			double p4_y;

			double temp3;
			double temp4;

			p1_x = x;
			p4_x = x2;
			p3_y = y2;
			p2_y = y;

			temp1 = (double)r0 / ((double)fabs(r1) + r0);
			temp2 = (double)r2 / ((double)fabs(r3) + r2);
			temp3 = (double)r2 / ((double)fabs(r1) + r2);
			temp4 = (double)r0 / ((double)fabs(r3) + r0);

			p1_y = y + (temp1 * unit);
			p4_y = y2 - (temp2 * unit);
			p3_x = x2 - (temp3 * unit);
			p2_x = x + (temp4 * unit);

			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p3_x, p3_y);
			glVertex2d(p4_x, p4_y);
			glEnd();
			//						continue;
		}
		// 5. r3 is -
		else if (r3 <= 0 && r1 > 0 && r2 >= 0) {
			p1_y = y;
			p2_x = x3;

			temp1 = (double)r0 / (double)(r0 + fabs(r3));
			temp2 = (double)r2 / (double)(r2 + fabs(r3));

			p1_x = x + ((double)temp1 * (double)unit);
			p2_y = y2 - ((double)temp2 * (double)unit);
		}
		// 6. r2 is -
		else if (r2 <= 0 && r1 > 0 && r3 >= 0) {
			p1_y = y1;
			p2_x = x3;

			temp1 = (double)r1 / (double)(r1 + fabs(r2));
			temp2 = (double)r3 / (double)(r3 + fabs(r2));

			p1_x = x1 + ((double)temp1 * (double)unit);
			p2_y = y3 + ((double)temp2 * (double)unit);
		}
		// 7. r1 is -
		else if (r1 <= 0 && r2 > 0 && r3 >= 0) {
			p1_x = x;
			p2_y = y2;

			temp1 = (double)r0 / (double)(r0 + fabs(r1));
			temp2 = (double)r2 / (double)(r2 + fabs(r1));

			p1_y = y + ((double)temp1 * (double)unit);
			p2_x = x2 - ((double)temp2 * (double)unit);
		}

		if (p1_x != -2.0 && p2_x != -2.0 && p1_y != -2.0 && p2_y != -2.0) {
			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p1_x, p1_y);
			glVertex2d(p2_x, p2_y);
			glEnd();
			free(cur_exp);
		}
	}
	else if (r0 <= 0) {
		// 1. r1, r2, r3 are +
		if (r1 > 0 && r2 > 0 && r3 > 0) {
			p1_x = x;
			p2_y = y;

			temp1 = (double)r1 / ((double)(fabs(r0) + r1));
			temp2 = (double)r3 / ((double)(fabs(r0) + r3));

			p1_y = y1 - (temp1 * unit);
			p2_x = x3 - (temp2 * unit);
		}
		// 2. r2, r3 are +
		else if (r2 > 0 && r3 > 0 && r1 <= 0) {
			p1_y = y1;
			p2_y = y;

			temp1 = (double)r2 / ((double)(fabs(r1) + r2));
			temp2 = (double)r3 / ((double)(fabs(r0) + r3));

			p1_x = x2 - (temp1 * unit);
			p2_x = x3 - (temp2 * unit);
		}
		// 3. r1, r2 are +
		else if (r1 > 0 && r2 > 0 && r3 <= 0) {
			p1_x = x1;
			p2_x = x2;

			temp1 = (double)r1 / ((double)fabs(r0) + r1);
			temp2 = (double)r2 / ((double)fabs(r3) + r2);

			p1_y = y1 - (temp1 * unit);
			p2_y = y2 - (temp2 * unit);
		}
		// 4. r1, r3 are +
		else if (r1 > 0 && r3 > 0 && r2 <= 0) {
			double p3_x;
			double p3_y;
			double p4_x;
			double p4_y;

			double temp3;
			double temp4;

			p1_x = x1;
			p2_y = y1;
			p3_y = y3;
			p4_x = x3;

			temp1 = (double)r1 / (double)(fabs(r0) + r1);
			temp2 = (double)r1 / (double)(fabs(r2) + r1);
			temp3 = (double)r3 / (double)(fabs(r0) + r3);
			temp4 = (double)r3 / (double)(fabs(r2) + r3);

			p1_y = y1 - (temp1 * unit);
			p2_x = x1 + (temp2 * unit);
			p3_x = x3 - (temp3 * unit);
			p4_y = y3 + (temp4 * unit);

			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p3_x, p3_y);
			glVertex2d(p4_x, p4_y);
			glEnd();
			//						continue;
		}
		// 5. r3 is +
		else if (r3 > 0 && r1 <= 0 && r2 <= 0) {
			p1_y = y;
			p2_x = x3;

			temp1 = (double)r3 / ((double)fabs(r0) + r3);
			temp2 = (double)r3 / ((double)fabs(r2) + r3);

			p1_x = x3 - (temp1 * unit);
			p2_y = y3 + (temp2 * unit);

		}
		// 6. r2 is +
		else if (r2 > 0 && r1 <= 0 && r3 <= 0) {
			p1_y = y1;
			p2_x = x3;

			temp1 = (double)r2 / ((double)(fabs(r1) + r2));
			temp2 = (double)r2 / ((double)(fabs(r3) + r2));

			p1_x = x2 - (temp1 * unit);
			p2_y = y2 - (temp2 * unit);
		}
		// 7. r1 is +
		else if (r1 > 0 && r2 <= 0 && r3 <= 0) {
			p1_x = x1;
			p2_y = y1;

			temp1 = (double)r1 / ((double)(fabs(r0) + r1));
			temp2 = (double)r1 / ((double)(fabs(r2) + r1));

			p1_y = y1 - ((double)temp1 * (double)unit);
			p2_x = x1 + ((double)temp2 * (double)unit);

		}

		if (p1_x != -2.0 && p2_x != -2.0 && p1_y != -2.0 && p2_y != -2.0) {
			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p1_x, p1_y);
			glVertex2d(p2_x, p2_y);
			glEnd();
			free(cur_exp);
		}
	}

}

void evaluate_graph_first(int value, const char *text) {
	double x;
	double y;
	int i;
	int j;
	int count = 0;
	for (i = 0; i <= value; i++) {
		x = ((double)i) / value;
		for (j = 0; j <= value; j++) {
			y = ((double)j) / value;
			// We already have coordinate of (x, y)
			// TODO: marching square to find curves
			// points around the current point
			draw_condition(x, y, value, text);
			draw_condition(-x, y, value, text);
			draw_condition(-x, -y, value, text);
			draw_condition(x, -y, value, text);
		}
	}
}
