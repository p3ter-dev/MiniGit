#include "./FileIO.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::string readFileContent(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) return "";

    std::ostringstream ss;
    ss << inFile.rdbuf();
    return ss.str();
}

std::vector<std::string> readStagedFiles() {
    std::ifstream stage(".minigit/stage");
    std::vector<std::string> files;
    std::string line;
    while (std::getline(stage, line)) {
        if (!line.empty())
            files.push_back(line);
    }
    return files;
}

std::string readCurrentHead() {
    std::ifstream refFile(".minigit/refs/main");
    std::string headHash;
    std::getline(refFile, headHash);
    return headHash.empty() ? "null" : headHash;
}