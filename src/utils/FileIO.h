#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <unordered_map>

namespace utils {

    std::string readFile(const std::string& filename);
    void writeFile(const std::string& path, const std::string& content);

    std::unordered_map<std::string, std::string> readIndex(const std::string& indexPath);
    void writeIndex(const std::string& indexPath, const std::unordered_map<std::string, std::string>& indexMap);

}

#endif
