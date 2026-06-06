#pragma once
#include "global.h"
#include <functional>

void set_pixel(int x, int y, Color color);
void render(const std::function<void()>& draw_code);