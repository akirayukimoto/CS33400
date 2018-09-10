#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Evpoly.h"
#include "freeglut.h"


void marching_rest_points(double x, double y, int value, const char *input_text);

void finding_line(int value, double real_x, 
	double real_y, const char* text);

void finding_curve(int value, double p1_x, double p1_y, double p2_x, 
	double p2_y, const char *text);