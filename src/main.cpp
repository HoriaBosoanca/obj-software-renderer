#include <algorithm>
#include "draw.h"
#include "load_obj.h"

#define CAM_SCALE 1.0f
int main() {
	Model model("../assets/in/diablo3_pose.obj");
	for (auto [a, b] : model.lines) {
		a = (a+1.0f)/2.0f/CAM_SCALE; b = (b+1.0f)/2.0f/CAM_SCALE;
		a.x *= WIDTH; a.y *= HEIGHT; b.x *= WIDTH; b.y *= HEIGHT;
		draw_line(a, b, RED);
	}
	render("../assets/out/render.png");
	return 0;
}