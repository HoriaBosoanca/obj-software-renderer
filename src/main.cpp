#include <algorithm>
#include "draw.h"
#include "load_obj.h"

int main() {
	std::vector<Line> lines = obj_get_lines("../assets/diablo3_pose.obj");
	for (Line l : lines) {
		Point a = l.first, b = l.second;
		a + 1.0f; b + 1.0f;
		a / 2.0f; b / 2.0f;
		a.x *= WIDTH;
		a.x = std::clamp(a.x, 0.0f, static_cast<float>(WIDTH - 1));
		a.y *= HEIGHT;
		a.y = std::clamp(a.y, 0.0f, static_cast<float>(HEIGHT - 1));
		b.x *= WIDTH;
		b.x = std::clamp(b.x, 0.0f, static_cast<float>(WIDTH - 1));
		b.y *= HEIGHT;
		b.y = std::clamp(b.y, 0.0f, static_cast<float>(HEIGHT - 1));
		draw_line(a, b, RED);
	}
	create_image();
	return 0;
}