#include "model.h"
#include "draw.h"
#include <fstream>
#include <sstream>

Model::Model(const std::string& obj_path) {
	std::ifstream in_file(obj_path);
	std::vector<Vec3> points;

	std::string line_str;
	while (std::getline(in_file, line_str)) {
		std::stringstream line_ss(line_str);
		std::string label; line_ss >> label;
		if (label == "v") {
			float x, y, z; line_ss >> x >> y >> z;
			points.emplace_back(x, y, z);
		} else if (label == "f") {
			std::string num_str;

			std::getline(line_ss, num_str, '/');
			int idx1 = std::stoi(num_str);
			std::getline(line_ss, num_str, ' ');

			std::getline(line_ss, num_str, '/');
			int idx2 = std::stoi(num_str);
			std::getline(line_ss, num_str, ' ');

			std::getline(line_ss, num_str, '/');
			int idx3 = std::stoi(num_str);
			std::getline(line_ss, num_str, '\n');

			triangles.emplace_back(points[idx1-1], points[idx2-1], points[idx3-1]);
		} else {
			// nothing for now
		}
	}
	in_file.close();
}

static void transform_triangle(Triangle2D& t) {
	t = (t*CAM_SCALE+1.0f)/2.0f*Vec2{WIDTH_PX, HEIGHT_PX};
}

void Model::draw() const {
	for (auto _t : triangles) {
		auto t = _t.to2D();
		transform_triangle(t);
		draw_triangle_fill(t, {rand_byte(), rand_byte(), rand_byte(), 255});
	}
}