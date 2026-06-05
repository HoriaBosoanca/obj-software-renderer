#pragma once

#include "types.h"
#include <vector>

struct Model {
	std::vector<Triangle> triangles;
	Model(const char* obj_path);
};
