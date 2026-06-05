#include "load_obj.h"
#include <fstream>
#include <sstream>

Model::Model(const char* obj_path) {
	std::ifstream in_file(obj_path);
	std::vector<Vec3> points;

	std::string line_str;
	while (std::getline(in_file, line_str)) {
		std::stringstream line_ss(line_str);
		std::string label; line_ss >> label;
		if (label == "v") {
			float x, y, z; line_ss >> x >> y >> z;
			points.push_back(Vec3{x, y, z});
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

			triangles.push_back(Triangle{points[idx1-1], points[idx2-1], points[idx3-1]});
		} else {
			// nothing for now
		}
	}
	in_file.close();
}