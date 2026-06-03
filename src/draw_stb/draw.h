#pragma once
#include "../types.h"

void render(const char* out_path);
void set_pixel(int x, int y, Color color);
void draw_line(Vec3 a, Vec3 b, Color color);