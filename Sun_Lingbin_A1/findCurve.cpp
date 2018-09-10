#include "findCurve.h"
#include <math.h>
using namespace std;


double points_pair[2][2];
double start_point[2];
double prev_point[2];

void marching_points_first(double x, double y, int value, const char *text) {
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
	free(cur_exp);
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
			if (p1_x == p2_x && p1_y == p2_y) {
				return;
			}
			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p1_x, p1_y);
			glVertex2d(p2_x, p2_y);
			glEnd();

			points_pair[0][0] = p1_x;
			points_pair[0][1] = p1_y;
			points_pair[1][0] = p2_x;
			points_pair[1][2] = p2_y;

			start_point[0] = p1_x;
			start_point[1] = p1_y;
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
			if (p1_x == p2_x && p1_y == p2_y) {
				return;
			}
			glBegin(GL_LINES);
			glColor3f(1, 1, 0);
			glVertex2d(p1_x, p1_y);
			glVertex2d(p2_x, p2_y);
			glEnd();

			start_point[0] = p1_x;
			start_point[1] = p1_y;

			points_pair[0][0] = p1_x;
			points_pair[0][1] = p1_y;
			points_pair[1][0] = p2_x;
			points_pair[1][2] = p2_y;
		}
	}


}

void marching_rest_points(double x, double y, int value, const char *input_text) {

	if (fabs(x) == 1.0 || fabs(y) == 1.0)
		return;

	double unit = (double)1 / (double)value;
	pExp *func;
	char *cur_exp = _strdup(input_text);
	func = readExp(cur_exp);
	free(cur_exp);
	double p0[2];
	for (int i = 0; i <= value; i++) {
		p0[0] = ((double)i) / value;
		if (x - p0[0] == 0)
			break;
		if (x - p0[0] < unit) {
			break;
		}
	}
	for (int j = 0; j <= value; j++) {
		p0[1] = ((double)j) / value;
		if (y - p0[1] == 0)
			break;
		if (y - p0[1] < unit) {
			break;
		}
	}

	cout << "p0: (" << p0[0] << ", " << p0[1] << ")" << endl;

	double p1[2];
	double p2[2];
	double p3[2];
	double p4[2];
	double p5[2];
	if (fmod(x, unit) == 0.0) {
		p1[0] = p0[0] - unit; p1[1] = p0[1];
		p2[0] = p0[0] - unit; p2[1] = p0[1] + unit;
		p3[0] = p0[0]; p3[1] = p0[1] + unit;
		p4[0] = p0[0] + unit; p4[1] = p0[1] + unit;
		p5[0] = p0[0] + unit; p5[1] = p0[1];
	}
	else if (fmod(y, unit) == 0.0) {
		p1[0] = p0[0]; p1[1] = p0[1] + unit;
		p2[0] = p0[0] + unit; p2[1] = p0[1] + unit;
		p3[0] = p0[0] + unit; p3[1] = p0[1];
		p4[0] = p0[0] + unit; p4[1] = p0[1] - unit;
		p5[0] = p0[0]; p5[1] = p0[1] - unit;
	}

	double r0 = func->eval(p0[0], p0[1]);
	double r1 = func->eval(p1[0], p1[1]);
	double r2 = func->eval(p2[0], p2[1]);
	double r3 = func->eval(p3[0], p3[1]);
	double r4 = func->eval(p4[0], p4[1]);
	double r5 = func->eval(p5[0], p5[1]);

	double temp[] = { -2, -2 };
	double next_point[2];
	// check the front block
	if (r0 > 0) {
		if (r1 > 0 && r2 > 0) {
			double ratio = (double)r2 / ((double)(fabs(r3) + r2));
			if (p2[0] == p3[0]) {
				temp[0] = p2[0];
				temp[1] = p2[1] - ratio * unit;
			}
			else if (p2[1] == p3[1]) {
				temp[1] = p2[1];
				temp[0] = p2[0] + ratio * unit;
			}
		}
		else if (r1 > 0 && r2 <= 0) {
			double ratio = (double)r1 / ((double)(fabs(r2) + r1));
			if (p1[0] == p2[0]) {
				temp[0] = p1[0];
				temp[1] = p1[1] + ratio * unit;
			}
			else if (p1[1] == p2[1]) {
				temp[1] = p1[1];
				temp[0] = p1[0] + ratio * unit;
			}
		}
		else if (r1 <= 0 && r2 <= 0) {
			double ratio = (double)r0 / ((double)(fabs(r1) + r0));
			if (p0[0] == p1[0]) {
				temp[0] = p0[0];
				temp[1] = p0[1] + ratio * unit;
			}
			else if (p0[1] == p1[1]) {
				temp[1] = p0[1];
				temp[0] = p0[0] - ratio * unit;
			}
		}
	}
	else if (r0 <= 0) {
		if (r1 > 0 && r2 > 0) {
			double ratio = (double)r1 / ((double)(fabs(r0) + r1));
			if (p0[0] == p1[0]) {
				temp[0] = p1[0];
				temp[1] = p1[1] - ratio * unit;
			}
			else if (p0[1] == p1[1]) {
				temp[1] = p1[1];
				temp[0] = p1[0] - ratio * unit;
			}
		}
		else if (r2 > 0 && r1 <= 0) {
			double ratio = (double)r2 / ((double)(fabs(r1) + r2));
			if (p1[0] == p2[0]) {
				temp[0] = p2[0];
				temp[1] = p2[1] - ratio * unit;
			}
			else if (p1[1] == p2[1]) {
				temp[1] = p2[1];
				temp[0] = p2[0] - ratio * unit;
			}
		}
		else if (r1 <= 0 && r2 <= 0) {
			double ratio = (double)r3 / ((double)(fabs(r2) + r3));
			if (p0[0] == p1[0]) {
				temp[0] = p3[0];
				temp[1] = p3[1] + ratio * unit;
			}
			else if (p0[1] == p1[1]) {
				temp[1] = p3[1];
				temp[0] = p3[0] - ratio * unit;
			}
		}
	}

	if (temp[0] == prev_point[0] && temp[1] == prev_point[1]) {
		// same point found
		if (r0 > 0) {
			if (r4 <= 0 && r5 <= 0) {
				double ratio = (double)r0 / ((double)(fabs(r5) + r0));
				if (p5[0] == p0[0]) {
					temp[0] = p5[0];
					temp[1] = p0[0] - ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[1] = p5[1];
					temp[0] = p0[0] + ratio * unit;
				}
			}
			else if (r4 <= 0 && r5 > 0) {
				double ratio = (double)r5 / ((double)(fabs(r4) + r5));
				if (p5[0] == p0[0]) {
					temp[1] = p5[1];
					temp[0] = p5[0] + ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[0] = p5[0];
					temp[1] = p0[1] + ratio * unit;
				}
			}
			else if (r4 > 0 && r5 > 0) {
				double ratio = (double)r4 / ((double)(fabs(r3) + r4));
				if (p5[0] == p0[0]) {
					temp[0] = p3[0];
					temp[1] = p4[1] - ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[1] = p4[1];
					temp[0] = p4[0] - ratio * unit;
				}
			}
		}
		else if (r0 <= 0) {
			if (r4 <= 0 && r5 <= 0) {
				double ratio = (double)r3 / ((double)(fabs(r4) + r3));
				if (p5[0] == p0[0]) {
					temp[0] = p3[0];
					temp[1] = p3[0] - ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[1] = p3[1];
					temp[0] = p3[0] + ratio * unit;
				}
			}
			else if (r4 > 0 && r5 <= 0) {
				double ratio = (double)r4 / ((double)(fabs(r5) + r4));
				if (p5[0] == p0[0]) {
					temp[1] = p4[1];
					temp[0] = p4[0] - ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[0] = p4[0];
					temp[1] = p4[1] - ratio * unit;
				}
			}
			else if (r4 > 0 && r5 > 0) {
				double ratio = (double)r5 / ((double)(fabs(r0) + r5));
				if (p5[0] == p0[0]) {
					temp[0] = p5[0];
					temp[1] = p5[1] + ratio * unit;
				}
				else if (p5[1] == p0[1]) {
					temp[1] = p5[1];
					temp[0] = p5[0] - ratio * unit;
				}
			}
		}
	}

	if (temp[0] != -2 && temp[1] != -2) {
		next_point[0] = temp[0];
		next_point[1] = temp[1];
		prev_point[0] = x;
		prev_point[1] = y;


		glBegin(GL_LINES);
		glColor3f(0.5f, 0, 0.5f);
		glVertex2d(x, y);
		glVertex2d(next_point[0], next_point[1]);
		glEnd();
	}

	marching_rest_points(next_point[0], next_point[1], value, input_text);
}

void finding_line(int value, double real_x, 
	double real_y, const char *input_text) {

	//cout << "hello! u r here!" << endl;
	if (real_x == -1 || real_x == 1 || real_y == -1 || real_y == 1) {
		return;
	}
	double x;
	double y;
	double unit = (double)1 / (double)value;

	for (int i = 0; i <= value; i++) {
		x = ((double)i) / value;
		if (real_x - x < unit) {
			break;
		}
	}
	for (int j = 0; j <= value; j++) {
		y = ((double)j) / value;
		if (real_y - y < unit) {
			break;
		}
	}

	marching_points_first(x, y, value, input_text);
	
	prev_point[0] = points_pair[1][0];
	prev_point[1] = points_pair[1][1];
	cout << "prev: (" << points_pair[0][0] << ", " << points_pair[0][1] << ")" << endl;
	cout << "prev: (" << points_pair[1][0] << ", " << points_pair[1][1] << ")" << endl;
	marching_rest_points(points_pair[0][0], points_pair[0][1], value, input_text);
	prev_point[0] = points_pair[0][0];
	prev_point[1] = points_pair[0][1];
	marching_rest_points(points_pair[1][0], points_pair[1][1], value, input_text);
}

void finding_curve(int value, double p1_x, double p1_y, double p2_x, 
	double p2_y, const char *text) {
	// finding mid point
	pExp *func;
	func = readExp(_strdup(text));
	double r1 = func->eval(p1_x, p1_y);
	double r2 = func->eval(p2_x, p2_y);

	double mid_x;
	double mid_y;
	double r_mid = -2.0;

	while (r1 != 0 && r2 != 0) {
		mid_x = (p1_x + p2_x) / (double)2;
		mid_y = (p1_y + p2_y) / (double)2;

		r_mid = func->eval(mid_x, mid_y);
		if (r_mid == 0) {
			break;
		}
		else if ((r1 < 0 && r2 > 0 && r_mid < 0) ||
			r1 > 0 && r2 < 0 && r_mid > 0) {
			r1 = r_mid;
			p1_x = mid_x;
			p1_y = mid_y;
		}
		else if ((r1 < 0 && r2 > 0 && r_mid > 0) ||
			(r1 > 0 && r2 < 0 && r_mid < 0)) {
			r2 = r_mid;
			p2_x = mid_x;
			p2_y = mid_y;
		}
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex2d(mid_x, mid_y);
		glEnd();
	}

	if (r1 == 0) {
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2d(p1_x, p1_y);
		glEnd();
		mid_x = p1_x;
		mid_y = p1_y;
		r_mid = r1;
	}
	else if (r2 == 0) {
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2d(p2_x, p2_y);
		glEnd();
		mid_x = p2_x;
		mid_y = p2_y;
		r_mid = r2;
	}
	else if (r_mid == 0) {
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2d(mid_x, mid_y);
		glEnd();
	}
	cout << "mid point pos: (" << mid_x << ", " << mid_y << ")" << endl;
	//cout << "hello! u r here!" << endl;
	finding_line(value, mid_x, mid_y, text);


}