#include "shaders.h"
std::string loadShaderSource(const std::string& filePath)
{
	std::ifstream file(filePath);

	if(!file)
	{
		std::cout << "Error opening: " << filePath << std::endl;
		return "";
	}

	std::stringstream buf;

	buf << file.rdbuf();

	return buf.str();
}
