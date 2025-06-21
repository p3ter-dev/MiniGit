#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace utils {

    std::string readFile(const std::string& filename) {
        std::ifstream fileIn(filename);
        return std::string((std::istreambuf_iterator<char>(fileIn)),
                            std::istreambuf_iterator<char>());
    }

    void writeFile(const std::string& path, const std::string& content) {
        std::ofstream fileOut(path);
        fileOut << content;
        fileOut.close();
    }

    std::unordered_map<std::string, std::string> readIndex(const std::string& indexPath) {
        std::unordered_map<std::string, std::string> map;
        std::ifstream in(indexPath);
        std::string line;

        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string filename, hash;
            if (iss >> filename >> hash) {
                map[filename] = hash;
            }
        }

        return map;
    }

    void writeIndex(const std::string& indexPath, const std::unordered_map<std::string, std::string>& indexMap) {
        std::ofstream out(indexPath);
        for (const auto& [filename, hash] : indexMap) {
            out << filename << " " << hash << "\n";
        }
    }

}
