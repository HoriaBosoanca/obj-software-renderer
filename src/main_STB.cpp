#include "draw_STB/draw.h"
#include "load_obj.h"

int main() {
	// const Model model("../assets/in/diablo3_pose.obj");
	// model.draw(RED);
	draw_triangle(Triangle{
		Vec3{7, 45, 0},
		Vec3{35, 100, 0},
		Vec3{45, 60, 0}},RED);
	draw_triangle(Triangle{
		Vec3{120, 35, 0},
		Vec3{90, 5, 0},
		Vec3{45, 110, 0}},WHITE);
	draw_triangle(Triangle{
		Vec3{115, 83, 0},
		Vec3{80, 90, 0},
		Vec3{85, 120, 0}},GREEN);
	render("../assets/out/render.png");
	return 0;
}