#include <algorithm>
#include "draw.h"
#include "load_obj.h"

#define CAM_SCALE 1.0f
void transform_triangle(Triangle& t) {
	for (Vec3* p : {&std::get<0>(t), &std::get<1>(t), &std::get<2>(t)}) {
		*p = (*p+1.0f)/2.0f/CAM_SCALE;
		p->x *= WIDTH; p->y *= HEIGHT;
	}
}

int main() {
	for (const Model model("../assets/in/diablo3_pose.obj");
		auto t : model.triangles) {
		transform_triangle(t);
		draw_triangle(t, RED);
	}
	render("../assets/out/render.png");
	return 0;
}