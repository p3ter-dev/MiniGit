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
    if (!in) {
        std::cerr << "Branch '" << targetBranch << "' does not exist.\n";
        return;
    }

    std::string targetCommit;
    std::getline(in, targetCommit);
    in.close();

    std::string base = findLCA(currentCommit, targetCommit);

    auto baseBlobs = getBlobs(base);
    auto currentBlobs = getBlobs(currentCommit);
    auto targetBlobs = getBlobs(targetCommit);

    bool conflictFound = false;

    for (const auto& [filename, baseHash] : baseBlobs) {
        std::string currentHash = currentBlobs[filename];
        std::string targetHash = targetBlobs[filename];

        if (currentHash != targetHash && currentHash != baseHash && targetHash != baseHash) {
            // Conflict
            conflictFound = true;
            std::cout << "CONFLICT: both modified " << filename << "\n";

            std::ifstream currentBlob(".minigit/objects/" + currentHash);
            std::ifstream targetBlob(".minigit/objects/" + targetHash);

            std::ofstream outFile(filename);
            outFile << "<<<<<<< current\n";
            outFile << currentBlob.rdbuf();
            outFile << "=======\n";
            outFile << targetBlob.rdbuf();
            outFile << ">>>>>>> " << targetBranch << "\n";
            outFile.close();

            std::cout << "Conflict markers written to " << filename << "\n";
            continue;
        }

        // Fast-forward merge
        if (targetHash != baseHash && currentHash == baseHash) {
            std::ifstream inBlob(".minigit/objects/" + targetHash);
            std::ofstream outFile(filename);
            outFile << inBlob.rdbuf();
            std::cout << "Merged " << filename << " from " << targetBranch << "\n";
        }
    }

    if (conflictFound) {
        std::cout << "\nMerge completed with conflicts.\n"
                     "Please resolve conflicts and commit manually.\n";
    } else {
        std::cout << "\nMerge finished successfully with no conflicts.\n";
    }
}