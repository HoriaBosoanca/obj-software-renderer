#include "draw.h"

int main() {
	Point a = {7, 3}, b = {12,37}, c = {62, 53};

	draw_line(a, b, BLUE);
	draw_line(b, c, GREEN);
	draw_line(c, a, YELLOW);
	draw_line(a, c, RED);

	set_pixel(a.x, a.y, WHITE);
	set_pixel(b.x, b.y, WHITE);
	set_pixel(c.x, c.y, WHITE);

	create_image();
	return 0;
}