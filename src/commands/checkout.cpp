#include "./checkout.h"
#include "../utils/FileIO.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void restoreFilesFromCommit(const std::string& commitHash) {
    fs::path repo = fs::current_path() / ".minigit";
    fs::path commitPath = repo / "commits" / commitHash;

    std::ifstream commitFile(commitPath);
    if (!commitFile) {
        std::cerr << "Error: Commit not found: " << commitHash << "\n";
        return;
    }

    std::string line;
    while (std::getline(commitFile, line)) {
        if (line.rfind("blob: ", 0) == 0) {
            std::string blobHash = line.substr(6);
            fs::path blobPath = repo / "objects" / blobHash;

            std::ifstream blobFile(blobPath);
            std::string content((std::istreambuf_iterator<char>(blobFile)), std::istreambuf_iterator<char>());
            blobFile.close();

            // TEMP: Using blobHash as filename (since your blobs don't store filenames yet)
            std::string filename = blobHash + ".txt";
            std::ofstream outFile(filename);
            outFile << content;
            outFile.close();
        }
    }
    commitFile.close();
}

void checkout(const std::string& target) {
    fs::path repo = fs::current_path() / ".minigit";
    fs::path refPath = repo / "refs" / target;

    if (fs::exists(refPath)) {
        std::ifstream branchFile(refPath);
        std::string commitHash;
        std::getline(branchFile, commitHash);
        branchFile.close();

        restoreFilesFromCommit(commitHash);

        std::ofstream headFile(repo / "HEAD");
        headFile << "ref: refs/" << target;
        headFile.close();

        std::cout << "Switched to branch '" << target << "'\n";
    } else {
        fs::path commitPath = repo / "commits" / target;
        if (!fs::exists(commitPath)) {
            std::cerr << "Error: branch or commit not found.\n";
            return;
        }

        restoreFilesFromCommit(target);

        std::ofstream headFile(repo / "HEAD");
        headFile << target;
        headFile.close();

        std::cout << "Detached HEAD at commit " << target << "\n";
    }
}


