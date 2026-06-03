#include <algorithm>
#include "draw.h"
#include "load_obj.h"

int main() {
	Model model("../assets/in/diablo3_pose.obj");
	for (auto [a, b] : model.lines) {
		a = (a+1.0f)/2.0f; b = (b+1.0f)/2.0f;
		a.x *= WIDTH; a.y *= HEIGHT; b.x *= WIDTH; b.y *= HEIGHT;
		a.x = std::clamp(a.x, 0.0f, static_cast<float>(WIDTH - 1));
		a.y = std::clamp(a.y, 0.0f, static_cast<float>(HEIGHT - 1));
		b.x = std::clamp(b.x, 0.0f, static_cast<float>(WIDTH - 1));
		b.y = std::clamp(b.y, 0.0f, static_cast<float>(HEIGHT - 1));
		draw_line(a, b, RED);
	}
	render("../assets/out/render.png");
	return 0;
}