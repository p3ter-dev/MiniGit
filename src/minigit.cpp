#include "MiniGit.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void MiniGit::init() {
    fs::path rootPath = fs::current_path().parent_path();
    fs::path minigitPath = rootPath / ".minigit";
    if (fs::exists(minigitPath)) {
        std::cout << "Repository already initialized.\n";
        return;
    }
    try {
        fs::create_directory(minigitPath);
        fs::create_directory(minigitPath / "objects");
        fs::create_directory(minigitPath / "commits");
        fs::create_directory(minigitPath / "refs");

        // Create HEAD file and set it to point to main branch
        std::ofstream headFile(minigitPath / "HEAD");
        headFile << "ref: refs/main";
        headFile.close();

        // Create initial main branch ref file
        std::ofstream masterRef(minigitPath / "refs/main");
        masterRef.close();

        std::cout << "Initialized empty MiniGit repository in .minigit/\n";
    } catch (const std::exception& e) {
        std::cerr << "Error initializing MiniGit: " << e.what() << "\n";
    }
}
