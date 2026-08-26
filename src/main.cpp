#include "backend.h"
#include "model.h"
#include "draw.h"
#include <iostream>

int main(const int argc, char* argv[]) {
	if (argc < 2) { std::cout << "Please specify a .obj input file!\n"; return 0; }
	const Model model(std::string("../assets/")+argv[1]);
	model.draw(RED);
	draw_triangle_fill(Triangle{
			Vec3{7, 45, 0},
			Vec3{35, 100, 0},
			Vec3{45, 60, 0}},RED);
	draw_triangle_fill(Triangle{
		Vec3{120, 35, 0},
		Vec3{90, 5, 0},
		Vec3{45, 110, 0}},WHITE);
	draw_triangle_fill(Triangle{
		Vec3{115, 83, 0},
		Vec3{80, 90, 0},
		Vec3{85, 120, 0}},GREEN);
	render();
	return 0;
}