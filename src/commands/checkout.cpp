#include "./checkout.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void checkout(const std::string& target) {
    fs::path repo = fs::current_path() / ".minigit";
    fs::path refPath = repo / "refs" / target;

    if (fs::exists(refPath)) {
        std::cout << "Switching to branch: " << target << "\n";
        // Restore files (next step)
    } else {
        std::cout << "Assuming target is a commit hash: " << target << "\n";
        // Restore files (next step)
    }
}

