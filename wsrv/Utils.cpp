#include "./Utils.h";
#include <sstream>
#include <iostream>
#include <fstream>

std::string Utils::readFileContents(const std::string& filePath)
{
	std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        // throw exception
        std::ostringstream msg;
        msg << "Utils::readFileContents(): error opening file: " << filePath;
        throw std::runtime_error(msg.str());
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); 
    std::string fileContents = buffer.str(); 
    return fileContents;
}
