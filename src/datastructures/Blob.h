#pragma once
#include <string>

class Blob {
public:
    std::string filename;
    std::string hash;

    Blob(const std::string& filename, const std::string& hash);
    void save(const std::string& content) const;
};
