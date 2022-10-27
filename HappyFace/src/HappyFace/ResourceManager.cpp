#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::string ResourceManager::loadFile(const std::filesystem::path& path) const
{
	std::ifstream in(path, std::ios::in);
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	if (!in) {
		std::cerr << "Resource Manager: File loading error: " + path.string() << " " << errno << std::endl;
		std::abort();
	}

	return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

}
