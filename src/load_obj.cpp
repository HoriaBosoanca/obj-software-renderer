#include "load_obj.h"
#include <cmath>
#include <fstream>
#include <sstream>

std::vector<Line> obj_get_lines(const char* obj_path) {
	std::ifstream in_obj(obj_path);

	std::vector<Point> points;
	std::vector<Line> lines;

	std::string in_line;
	while (std::getline(in_obj, in_line)) {
		std::stringstream line_ss(in_line);
		std::string data_format; line_ss >> data_format;
		if (data_format == "v") {
			float x, y, z; line_ss >> x >> y >> z;
			points.push_back(Point{x, y});
		} else if (data_format == "f") {
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

			lines.push_back(Line{points[idx1-1], points[idx2-1]});
			lines.push_back(Line{points[idx2-1], points[idx3-1]});
			lines.push_back(Line{points[idx3-1], points[idx1-1]});
		} else {
			// nothing for now
		}
	}

	return lines;
}
