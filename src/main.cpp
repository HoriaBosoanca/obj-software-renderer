#include "draw.h"
#include "load_obj.h"

int main() {
	const Model model("../assets/in/diablo3_pose.obj");
	model.draw();
	render("../assets/out/render.png");
	return 0;
}