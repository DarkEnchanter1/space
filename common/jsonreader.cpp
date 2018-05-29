#include <fstream>
#include "jsonreader.hpp"
using json = nlohmann::json;
json func(std::string jsonfile) {
	std::ifstream t(jsonfile);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return json::parse(buffer.str());
}