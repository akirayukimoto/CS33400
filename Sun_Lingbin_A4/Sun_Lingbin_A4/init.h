#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include "prop.h"

using namespace std;

p_color c1(0.93, 0.44, 0.69);
p_color c2(0.98, 0.75, 0.0);
p_color c3(0.49, 0.44, 0.92);

vector<p_pieces> p_list;
//vector<p_pieces> to_move;
p_pieces to_move[24];
p_pieces to_go[6][4];
bool p_switch[6][4];

int num_pieces = 24;

vector<point> rec_vertex(GLfloat org_x, GLfloat org_y, GLfloat u_w, GLfloat u_h) {
	vector<point> res;
	point p1(org_x, org_y);
	point p2(org_x + u_w, org_y);
	point p3(org_x + u_w, org_y - u_h);
	point p4(org_x, org_y - u_h);
	point c(org_x + (u_w / 2), org_y - (u_h / 2));

	res.push_back(p1);
	res.push_back(p2);
	res.push_back(p3);
	res.push_back(p4);
	res.push_back(c);

	return res;
}

// fill up pieces in colors and points
void fill_pieces(GLfloat w, GLfloat h, GLfloat u_w, GLfloat u_h) {
	
	GLfloat n_w;
	GLfloat n_h;
	vector<point> res;

	// piece 1
	n_w = w;
	n_h = h;
	p_color col[4];
	col[0] = c1;
	col[1] = c1;
	col[2] = c1;
	col[3] = c1;
	point pts[5];
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece1 = p_pieces(pts, col);
	p_list.push_back(piece1);

	// piece 2
	n_w = w + u_w;
	n_h = h;
	col[0] = c2;
	col[1] = c1;
	col[2] = c1;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece2(pts, col);
	p_list.push_back(piece2);

	// piece 3
	n_w = w + 2 * u_w;
	n_h = h;
	col[0] = c2;
	col[1] = c2;
	col[2] = c1;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece3(pts, col);
	p_list.push_back(piece3);

	// piece 4
	n_w = w + 3 * u_w;
	n_h = h;
	col[0] = c2;
	col[1] = c3;
	col[2] = c1;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece4(pts, col);
	p_list.push_back(piece4);

	// piece 5
	n_w = w;
	n_h = h - u_h;
	col[0] = c2;
	col[1] = c1;
	col[2] = c2;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece5(pts, col);
	p_list.push_back(piece5);

	// piece 6
	n_w = w + u_w;
	n_h = h - u_h;
	col[0] = c3;
	col[1] = c1;
	col[2] = c1;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece6(pts, col);
	p_list.push_back(piece6);

	// piece 7
	n_w = w + 2 * u_w;
	n_h = h - u_h;
	col[0] = c3;
	col[1] = c1;
	col[2] = c3;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece7(pts, col);
	p_list.push_back(piece7);

	// piece 8
	n_w = w + 3 * u_w;
	n_h = h - u_h;
	col[0] = c3;
	col[1] = c2;
	col[2] = c1;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece8(pts, col);
	p_list.push_back(piece8);

	// piece 9
	n_w = w;
	n_h = h - 2 * u_h;
	col[0] = c3;
	col[1] = c1;
	col[2] = c3;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece9(pts, col);
	p_list.push_back(piece9);

	// piece 10
	n_w = w + u_w;
	n_h = h - 2 * u_h;
	col[0] = c2;
	col[1] = c1;
	col[2] = c3;
	col[3] = c1;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece10(pts, col);
	p_list.push_back(piece10);

	// piece 11
	n_w = w + 2 * u_w;
	n_h = h - 2 * u_h;
	col[0] = c1;
	col[1] = c2;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece11(pts, col);
	p_list.push_back(piece11);

	// piece 12
	n_w = w + 3 * u_w;
	n_h = h - 2 * u_h;
	col[0] = c3;
	col[1] = c2;
	col[2] = c1;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece12(pts, col);
	p_list.push_back(piece12);

	// piece 13
	n_w = w;
	n_h = h - 3 * u_h;
	col[0] = c3;
	col[1] = c2;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece13(pts, col);
	p_list.push_back(piece13);

	// piece 14
	n_w = w + u_w;
	n_h = h - 3 * u_h;
	col[0] = c3;
	col[1] = c1;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece14(pts, col);
	p_list.push_back(piece14);

	// piece 15
	n_w = w + 2 * u_w;
	n_h = h - 3 * u_h;
	col[0] = c1;
	col[1] = c3;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece15(pts, col);
	p_list.push_back(piece15);

	// piece 16
	n_w = w + 3 * u_w;
	n_h = h - 3 * u_h;
	col[0] = c2;
	col[1] = c2;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece16(pts, col);
	p_list.push_back(piece16);

	// piece 17
	n_w = w;
	n_h = h - 4 * u_h;
	col[0] = c3;
	col[1] = c2;
	col[2] = c3;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece17(pts, col);
	p_list.push_back(piece17);

	// piece 18
	n_w = w + u_w;
	n_h = h - 4 * u_h;
	col[0] = c3;
	col[1] = c3;
	col[2] = c2;
	col[3] = c2;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece18(pts, col);
	p_list.push_back(piece18);

	// piece 19
	n_w = w + 2 * u_w;
	n_h = h - 4 * u_h;
	col[0] = c1;
	col[1] = c3;
	col[2] = c3;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece19(pts, col);
	p_list.push_back(piece19);

	// piece 20
	n_w = w + 3 * u_w;
	n_h = h - 4 * u_h;
	col[0] = c1;
	col[1] = c2;
	col[2] = c3;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece20(pts, col);
	p_list.push_back(piece20);

	// piece 21
	n_w = w;
	n_h = h - 5 * u_h;
	col[0] = c1;
	col[1] = c3;
	col[2] = c2;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece21(pts, col);
	p_list.push_back(piece21);

	// piece 22
	n_w = w + 1 * u_w;
	n_h = h - 5 * u_h;
	col[0] = c2;
	col[1] = c3;
	col[2] = c3;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece22(pts, col);
	p_list.push_back(piece22);

	// piece 23
	n_w = w + 2 * u_w;
	n_h = h - 5 * u_h;
	col[0] = c2;
	col[1] = c1;
	col[2] = c3;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece23(pts, col);
	p_list.push_back(piece23);

	// piece 24
	n_w = w + 3 * u_w;
	n_h = h - 5 * u_h;
	col[0] = c3;
	col[1] = c3;
	col[2] = c3;
	col[3] = c3;
	res = rec_vertex(n_w, n_h, u_w, u_h);
	copy(res.begin(), res.end(), pts);
	p_pieces piece24(pts, col);
	p_list.push_back(piece24);

}

void init_goal(GLfloat w, GLfloat h, GLfloat u_w, GLfloat u_h) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			GLfloat lu_x = w + i * u_w;
			GLfloat lu_y = h - j * u_h;
			GLfloat ru_x = w + (i + 1) * u_w;
			GLfloat ru_y = h - j * u_h;
			GLfloat rd_x = w + (i + 1) * u_w;
			GLfloat rd_y = h - (j + 1) * u_h;
			GLfloat ld_x = w + i * u_w;
			GLfloat ld_y = h - (j + 1) * u_h;
			GLfloat ct_x = w + i * u_w + (u_w / 2);
			GLfloat ct_y = h - j * u_h - (u_w / 2);

			point pts[5];
			point lu(lu_x, lu_y);
			point ru(ru_x, ru_y);
			point rd(rd_x, rd_y);
			point ld(ld_x, ld_y);
			point ct(ct_x, ct_y);
			pts[0] = lu;
			pts[1] = ru;
			pts[2] = rd;
			pts[3] = ld;
			pts[4] = ct;

			p_color cls[4];
			cls[0] = p_color(1, 1, 1);
			cls[1] = p_color(1, 1, 1);
			cls[2] = p_color(1, 1, 1);
			cls[3] = p_color(1, 1, 1);
		
			p_pieces piece(pts, cls);
			to_go[i][j] = piece;
		}
	}
}

void init_switch() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			p_switch[i][j] = TRUE;
		}
	}
}

void copy_array(vector<p_pieces> pieces, p_pieces *arr) {
	int i = 0;
	for (vector<p_pieces>::iterator it = pieces.begin(); it != pieces.end(); it++) {
		GLfloat lu_x = it->lu().x();
		GLfloat lu_y = it->lu().y();
		GLfloat ru_x = it->ru().x();
		GLfloat ru_y = it->ru().y();
		GLfloat rd_x = it->rd().x();
		GLfloat rd_y = it->rd().y();
		GLfloat ld_x = it->ld().x();
		GLfloat ld_y = it->ld().y();
		GLfloat ct_x = it->ct().x();
		GLfloat ct_y = it->ct().y();

		p_color col1(it->s1().r(), it->s1().g(), it->s1().b());
		p_color col2(it->s2().r(), it->s2().g(), it->s2().b());
		p_color col3(it->s3().r(), it->s3().g(), it->s3().b());
		p_color col4(it->s4().r(), it->s4().g(), it->s4().b());

		point pts[5];
		point lu(lu_x, lu_y);
		point ru(ru_x, ru_y);
		point rd(rd_x, rd_y);
		point ld(ld_x, ld_y);
		point ct(ct_x, ct_y);
		pts[0] = lu;
		pts[1] = ru;
		pts[2] = rd;
		pts[3] = ld;
		pts[4] = ct;

		p_color cls[4];
		cls[0] = col1;
		cls[1] = col2;
		cls[2] = col3;
		cls[3] = col4;

		cout << "lu pos: (" << to_move[i].lu().x() << ", " << to_move[i].lu().y() << ")" << endl;
		cout << "ru pos: (" << to_move[i].ru().x() << ", " << to_move[i].ru().y() << ")" << endl;
		cout << "rd pos: (" << to_move[i].rd().x() << ", " << to_move[i].rd().y() << ")" << endl;
		cout << "ld pos: (" << to_move[i].ld().x() << ", " << to_move[i].ld().y() << ")" << endl;
		cout << "ct pos: (" << to_move[i].ct().x() << ", " << to_move[i].ct().y() << ")" << endl;


		to_move[i++] = p_pieces(pts, cls);
	}
}