#include "Blob.h"
#include "../utils/FileIO.h"
#include "../utils/Hasher.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Blob::Blob(const std::string& filename)
    : filename(filename) {
    readAndHashFile();
}

void Blob::readAndHashFile() {
    // Read file content
    content = utils::readFile(filename);
    // Hash content
    hash = utils::computeSHA1(content);
}

void Blob::writeToObjectStore() const {
    std::string objectPath = ".minigit/objects/" + hash;

    // Only write if it doesn't already exist
    if (!fs::exists(objectPath)) {
        utils::writeFile(objectPath, content);
        std::cout << "Blob created: " << hash << "\n";
    } else {
        std::cout << "Blob already exists: " << hash << "\n";
    }
}

std::string Blob::getHash() const {
    return hash;
}

std::string Blob::getFilename() const {
    return filename;
}
