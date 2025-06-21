#include "add.h"
#include "../../utils/Hasher.h"
#include "../../utils/FileIO.h"
#include "../../datastructures/Blob.h"
#include <iostream>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace command {

    void addFile(const std::string& filename) {
        std::string indexFile = ".minigit/index";

        // 1. Check if file exists
        if (!fs::exists(filename)) {
            std::cerr << "Error: File '" << filename << "' not found.\n";
            return;
        }

        // 2. Use Blob class to read content, compute hash, and write blob
        Blob blob(filename);
        blob.writeToObjectStore();
        std::string hash = blob.getHash();

        // 3. Load and update index
        auto indexMap = utils::readIndex(indexFile);

        if (indexMap.find(filename) != indexMap.end()) {
            if (indexMap[filename] == hash) {
                std::cout << "No changes detected in '" << filename << "'.\n";
                return;
            } else {
                std::cout << "File updated in index.\n";
            }
        } else {
            std::cout << "File added to index.\n";
        }

        indexMap[filename] = hash;
        utils::writeIndex(indexFile, indexMap);
    }

}




