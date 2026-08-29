#pragma once

#include "global.h"
#include <string>
#include <vector>

struct Model {
	std::vector<Triangle3D> triangles;
	explicit Model(const std::string& obj_path);
	void draw() const;
};
