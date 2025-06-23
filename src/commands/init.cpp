#include "./init.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void initRepo() {
    fs::path rootPath = fs::current_path();
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

        std::ofstream headFile(minigitPath / "HEAD");
        headFile << "ref: refs/main";
        headFile.close();

        std::ofstream masterRef(minigitPath / "refs/main");
        masterRef.close();

        std::cout << "Initialized empty MiniGit repository in .minigit/\n";
    } catch (const std::exception& e) {
        std::cerr << "Error initializing MiniGit: " << e.what() << "\n";
    }
}
// This function initializes a new MiniGit repository in the current directory.