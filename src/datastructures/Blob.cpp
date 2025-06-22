#include "./Blob.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

Blob::Blob(const std::string& filename, const std::string& hash)
    : filename(filename), hash(hash) {}

void Blob::save(const std::string& content) const {
    fs::path objectsPath = fs::current_path() / ".minigit" / "objects";
    fs::create_directories(objectsPath);
    std::ofstream outFile(objectsPath / hash);
    outFile << content;
    outFile.close();
}
