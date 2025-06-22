#include "./log.h"
#include "../utils/FileIO.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


namespace fs = std::filesystem;


namespace command {
    void showLog() {
        fs::path repo = fs::current_path() / ".minigit";

        // Step 1: Get the current HEAD pointer
        std::ifstream headFile(repo / "HEAD");
        std::string headRef;
        std::getline(headFile, headRef);
        headFile.close();

        if (headRef.rfind("ref: ", 0) != 0) {
            std::cerr << "HEAD is in an invalid format.\n";
            return;
        }

        std::string branchPath = headRef.substr(5); // e.g., "refs/main"
        std::ifstream branchFile(repo / branchPath);
        std::string currentHash;
        std::getline(branchFile, currentHash);
        branchFile.close();

        if (currentHash.empty() || currentHash == "null") {
            std::cout << "No commits yet.\n";
            return;
        }

        // Step 2: Traverse and display commits
        while (!currentHash.empty() && currentHash != "null") {
            fs::path commitPath = repo / "commits" / currentHash;
            std::ifstream commitFile(commitPath);

            if (!commitFile) {
                std::cerr << "Error: Cannot find commit " << currentHash << "\n";
                break;
            }

            std::string line, timestamp, message, parent;
            while (std::getline(commitFile, line)) {
                if (line.rfind("timestamp: ", 0) == 0)
                    timestamp = line.substr(11);
                else if (line.rfind("message: ", 0) == 0)
                    message = line.substr(9);
                else if (line.rfind("parent: ", 0) == 0)
                    parent = line.substr(8);
            }
            commitFile.close();

            std::cout << "Commit: " << currentHash << "\n";
            std::cout << "Date:   " << timestamp << "\n";
            std::cout << "Message: " << message << "\n\n";

            currentHash = parent;
        }
    }
}


