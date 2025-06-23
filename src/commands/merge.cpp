#include "./merge.h"
#include "../utils/FileIO.h"
#include "../utils/Hasher.h"
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

std::string findLCA(const std::string& current, const std::string& other) {
    std::unordered_set<std::string> ancestors;
    std::string temp = current;
    while (!temp.empty() && temp != "null") {
        ancestors.insert(temp);
        temp = readParentHash(temp);
    }

    temp = other;
    while (!temp.empty() && temp != "null") {
        if (ancestors.count(temp)) return temp;
        temp = readParentHash(temp);
    }

    return "null";
}

std::unordered_map<std::string, std::string> getBlobs(const std::string& commitHash) {
    std::unordered_map<std::string, std::string> blobs;
    std::ifstream file(".minigit/commits/" + commitHash);
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("blob: ", 0) == 0) {
            std::string hash = line.substr(6);
            blobs[hash + ".txt"] = hash;
        }
    }
    return blobs;
}

void merge(const std::string& targetBranch) {
    std::string currentCommit = readCurrentHead();

    std::ifstream in(".minigit/refs/" + targetBranch);
    std::string targetCommit;
    std::getline(in, targetCommit);
    in.close();

    std::string base = findLCA(currentCommit, targetCommit);

    auto baseBlobs = getBlobs(base);
    auto currentBlobs = getBlobs(currentCommit);
    auto targetBlobs = getBlobs(targetCommit);

    for (const auto& [filename, baseHash] : baseBlobs) {
        std::string currentHash = currentBlobs[filename];
        std::string targetHash = targetBlobs[filename];

        if (currentHash != targetHash && currentHash != baseHash && targetHash != baseHash) {
            std::cout << "CONFLICT: both modified " << filename << "\n";
            continue;
        }

        if (targetHash != baseHash && currentHash == baseHash) {
            std::ifstream inBlob(".minigit/objects/" + targetHash);
            std::ofstream outFile(filename);
            outFile << inBlob.rdbuf();
            std::cout << "Merged " << filename << " from " << targetBranch << "\n";
        }
    }

    std::cout << "Merge finished.\n";
}