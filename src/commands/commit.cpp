#include "./commit.h"
#include "../utils/FileIO.h"
#include "../utils/Hasher.h"
#include "../datastructures/commit.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

void commit(const std::string& message) {
    fs::path repo = fs::current_path() / ".minigit";

    // Load staged blob hashes
    std::vector<std::string> blobHashes = readStagedFiles(); // from .minigit/stage
    if (blobHashes.empty()) {
        std::cout << "Nothing to commit. Stage some files first.\n";
        return;
    }

    // Load HEAD (parent commit hash)
    std::string parentHash = readCurrentHead(); // from refs/main

    // Get timestamp
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timestamp = std::ctime(&now);
    timestamp.pop_back();

    // Create commit hash
    std::string combinedData = timestamp + message + parentHash;
    std::string commitHash = simpleHash(combinedData);

    // Create commit object file
    fs::path commitPath = repo / "commits" / commitHash;
    std::ofstream out(commitPath);
    out << "commit: " << commitHash << "\n";
    out << "timestamp: " << timestamp << "\n";
    out << "message: " << message << "\n";
    out << "parent: " << parentHash << "\n";
    for (const std::string& blobHash : blobHashes) {
        out << "blob: " << blobHash << "\n";
    }
    out.close();

    // Update branch pointer and HEAD
    std::ofstream branchOut(repo / "refs/main", std::ios::trunc);
    branchOut << commitHash;
    branchOut.close();

    std::ofstream headOut(repo / "HEAD", std::ios::trunc);
    headOut << "ref: refs/main\n";
    headOut.close();

    // Clear staging area
    std::ofstream clearStage(repo / "stage", std::ios::trunc);
    clearStage.close();

    std::cout << "Committed as " << commitHash << "\n";
}
