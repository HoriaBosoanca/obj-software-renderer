#include "backend.h"
#include "model.h"
#include "draw.h"
#include <iostream>

int main(const int argc, char* argv[]) {
	init();
	if (argc < 2) { std::cout << "Please specify a .obj input file!\n"; return 0; }
	const Model model(argv[1]);
	model.draw();
	draw_triangle_fill(Triangle2D{
			Vec2{7, 45},
			Vec2{35, 100},
			Vec2{45, 60}},RED);
	draw_triangle_fill(Triangle2D{
		Vec2{120, 35},
		Vec2{90, 5},
		Vec2{45, 110}},WHITE);
	draw_triangle_fill(Triangle2D{
		Vec2{115, 83},
		Vec2{80, 90},
		Vec2{85, 120}},GREEN);
	render();
	return 0;
}