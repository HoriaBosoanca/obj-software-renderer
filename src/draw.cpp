#include "draw.h"
#include "backend.h"
#include <algorithm>
#include <cmath>

static void bad_draw_line(const Vec2 A, const Vec2 B, const Color& col) {
	for (float t = 0; t < 1; t+=.02) {
		const int x = std::round(A.x+(B.x-A.x)*t);
		const int y = std::round(A.y+(B.y-A.y)*t);
		set_pixel(x, y, col);
	}
}

static void better_draw_line(Vec2 A, Vec2 B, const Color& col) {
	const bool steep = std::abs(A.x-B.x) < std::abs(A.y-B.y);
	if (steep) {
		std::swap(A.x, A.y);
		std::swap(B.x, B.y);
	}
	if (A.x > B.x) {
		std::swap(A, B);
	}
	for (int x = A.x; x <= B.x; x++) {
		const float t = (x-A.x)/(B.x-A.x);
		const int y = std::round(A.y+(B.y-A.y)*t);
		if (steep) {
			set_pixel(y, x, col);
		} else {
			set_pixel(x, y, col);
		}
	}
}

void draw_triangle_empty(const Triangle2D& t, const Color& col) {
	better_draw_line(t.A, t.B, col);
	better_draw_line(t.B, t.C, col);
	better_draw_line(t.C, t.A, col);
}

static void scanline_fill_triangle(const Triangle2D& t, const Color& col) {
	Vec2 A = t.A, B = t.B, C = t.C;
	if (A.y < B.y) std::swap(A, B);
	if (A.y < C.y) std::swap(A, C);
	if (B.y < C.y) std::swap(B, C);
	// A top, B mid, C bottom
	const float mab = (A.y-B.y)/(A.x-B.x),
				mac = (A.y-C.y)/(A.x-C.x),
				mbc = (B.y-C.y)/(B.x-C.x);
	for (float yi = A.y; yi >= B.y; yi -= 0.02f) {
		// d: y-yi=0, so y=yi this is the scan-line at height yi
		// AB: y-ya=mab*(x-xa)
		// the intersection of d and AB is the start point of the scan-line
		float x1 = (yi-A.y)/mab+A.x;
		// AC: y-ya=mac*(x-xa)
		// the intersection of d and AC is the end point of the scan-line
		float x2 = (yi-A.y)/mac+A.x;
		if (x1 > x2) std::swap(x1, x2);
		for (float xi = x1; xi <= x2; xi += 0.02f) {
			set_pixel(xi, yi, col);
		}
	}
	for (float yi = B.y; yi >= C.y; yi -= 0.02f) {
		float x1 = (yi-B.y)/mbc+B.x;
		float x2 = (yi-A.y)/mac+A.x;
		if (x1 > x2) std::swap(x1, x2);
		for (float xi = x1; xi <= x2; xi += 0.02f) {
			set_pixel(xi, yi, col);
		}
	}
}

/*
 * We have a triangle A B C
 * Using the right-hand rule, we notice that
 * given a point (P) outside the triangle, relative to a side (say AB - out of the three sides AB, BC, CA of the triangle ABC),
 * the z component of the cross product of vec(P, A) and vec(P, B) is negative
 * if P is inside, it's positive
 *
 * Here is proof that the sign of the z component of the cross product of vec(A, B) and vec(A, C) is
 * the same as the sign of the signed triangle area of triangle ABC:
 * given A = (x1, y1), B = (x2, y2), C = (x3, y3), lifted to 3D with z = 0:
 * vec(A, B) = (x2 - x1, y2 - y1, 0)
 * vec(A, C) = (x3 - x1, y3 - y1, 0)
 * then
 * (vec(A, B) x vec(A, C))_z
 *
 *   | i        j        k |
 * = | x2 - x1  y2 - y1  0 | . k (cross product as formal determinant, where i, j, k are unit vectors)
 *   | x3 - x1  y3 - y1  0 |
 *
 *   | x2 - x1  y2 - y1 |
 * = | x3 - x1  y3 - y1 | (because k . k = 1)
 *
 *   | x1       y1       1 |
 * = | x2 - x1  y2 - y1  0 | (reverse of expansion along column 3)
 *   | x3 - x1  y3 - y1  0 |
 *
 *   | x1  y1  1 |
 * = | x2  y2  1 | (R2 + R1, R3 + R1 do not change the determinant)
 *   | x3  y3  1 |
 *
 * = 2 * S(ABC) (definition of signed triangle area)
 * so sign((vec(A, B) x vec(A, C))_z) = sign(S(ABC))
 *
 * Here is how to compute the signed triangle area:
 *
 * | x1  y1  1 |
 * | x2  y2  1 |
 * | x3  y3  1 |
 *
 * = x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3 (rule of Sarrus)
 * = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)
 * = - x1*(y3-y2) + x2*(y3-y1) - x3*(y2-y1)
 * = - x1*((y3-y1)-(y2-y1)) + x2*(y3-y1) - x3*(y2 - y1)
 * = (x2 - x1)*(y3 - y1) + (x1 - x3)*(y2 - y1)
 * = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)
*/

static double signed_triangle_area(const Vec2 a, const Vec2 b, const Vec2 c) {
	return .5*((b.y-a.y)*(b.x+a.x) + (c.y-b.y)*(c.x+b.x) + (a.y-c.y)*(a.x+c.x));
}

static void bbox_fill_triangle(const Triangle2D& t, const Color& col) {
	const Vec2 A = t.A, B = t.B, C = t.C;
	const Vec2 bbmin = {
		std::min(std::min(A.x, B.x), C.x),
		std::min(std::min(A.y, B.y), C.y)
	}, bbmax = {
		std::max(std::max(A.x, B.x), C.x),
		std::max(std::max(A.y, B.y), C.y)
	};
	const double total_area = signed_triangle_area(A, B, C);
	if (total_area < 1.0) return;
#pragma omp parallel for
	for (int x = bbmin.x; x <= bbmax.x; x++) {
		for (int y = bbmin.y; y <= bbmax.y; y++) {
			if (const Vec2 P = {static_cast<float>(x), static_cast<float>(y)};
				signed_triangle_area(P, B, C) / total_area < 0 ||
				signed_triangle_area(P, C, A) / total_area < 0 ||
				signed_triangle_area(P, A, B) / total_area < 0) {
				continue;
			}
			set_pixel(x, y, col);
		}
	}
}

void draw_triangle_fill(const Triangle2D& t, const Color& col) {
	bbox_fill_triangle(t, col);
}