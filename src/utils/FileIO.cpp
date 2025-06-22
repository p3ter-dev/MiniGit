#include "./FileIO.h"
#include <fstream>
#include <sstream>

std::string readFileContent(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) return "";

    std::ostringstream ss;
    ss << inFile.rdbuf();
    return ss.str();
}