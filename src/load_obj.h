#pragma once

#include "types.h"
#include <vector>

struct Model {
	std::vector<Line> lines;
	Model(const char* obj_path);
};
