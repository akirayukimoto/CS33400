#pragma once
#include "GL/glut.h"

class point {
public:
	point(){}
	~point(){}
	GLfloat e[2];

	point(GLfloat e0, GLfloat e1) {
		e[0] = e0;
		e[1] = e1;
	}

	inline GLfloat x() { return e[0]; }
	inline GLfloat y() { return e[1]; }

	inline GLfloat operator[] (int i) const { return e[i]; }
	inline GLfloat& operator[](int i) { return e[i]; };

};

inline void set_new_value(point p, GLfloat n_x, GLfloat n_y) {
	p[0] = n_x;
	p[1] = n_y;
}

class p_color {
public:
	p_color(){}
	GLfloat e[3];
	~p_color(){}

	p_color(GLfloat e0, GLfloat e1, GLfloat e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline GLfloat r() { return e[0]; }
	inline GLfloat g() { return e[1]; }
	inline GLfloat b() { return e[2]; }

	inline GLfloat operator[] (int i) const { return e[i]; }
	inline GLfloat& operator[](int i) { return e[i]; };
};

inline bool compare(p_color c1, p_color c2) {
	if (c1.r() == c2.r()
		&& c1.g() == c2.g()
		&& c1.b() == c2.b()) {
		return TRUE;
	}
	else 
		return FALSE;
}

class p_pieces {
public:
	p_pieces(){}
	~p_pieces(){}
	point p[5];
	p_color c[4];

	p_pieces(point p0[5], p_color c0[4]) {
		p[0] = p0[0];
		p[1] = p0[1];
		p[2] = p0[2];
		p[3] = p0[3];
		p[4] = p0[4];

		c[0] = c0[0];
		c[1] = c0[1];
		c[2] = c0[2];
		c[3] = c0[3];
	}

	inline point lu() { return p[0]; }
	inline point ru() { return p[1]; }
	inline point rd() { return p[2]; }
	inline point ld() { return p[3]; }
	inline point ct() { return p[4]; }

	inline p_color s1() { return c[0]; }
	inline p_color s2() { return c[1]; }
	inline p_color s3() { return c[2]; }
	inline p_color s4() { return c[3]; }

	inline void clear() {
		
	}
};

