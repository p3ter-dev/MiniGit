#include "./add.h"
#include "../utils/FileIO.h"
#include "../utils/Hasher.h"
#include "../datastructures/Blob.h"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

void addFileToStage(const std::string& filename) {
    fs::path filePath = fs::current_path() / filename;
    if (!fs::exists(filePath)) {
        std::cerr << "Error: file '" << filename << "' is not found.\n";
        return;
    }

    std::string content = readFileContent(filePath.string());
    std::string hash = simpleHash(content);

    Blob blob(filename, hash);
    blob.save(content);

    std::cout << "staged: " << filename << " (" << hash << ")\n";
}