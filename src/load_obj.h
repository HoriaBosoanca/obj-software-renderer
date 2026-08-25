#pragma once

#include "global.h"
#include <string>
#include <vector>

struct Model {
	std::vector<Triangle> triangles;
	Model(std::string obj_path);
	void draw(Color c) const;
};
