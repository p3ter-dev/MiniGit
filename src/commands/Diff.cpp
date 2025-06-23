#include "./diff.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void diff(const std::string& hash1, const std::string& hash2) {
    std::ifstream c1(".minigit/commits/" + hash1);
    std::ifstream c2(".minigit/commits/" + hash2);

    std::string line1, line2;
    std::vector<std::string> blobs1, blobs2;

    while (std::getline(c1, line1))
        if (line1.rfind("blob: ", 0) == 0)
            blobs1.push_back(line1.substr(6));

    while (std::getline(c2, line2))
        if (line2.rfind("blob: ", 0) == 0)
            blobs2.push_back(line2.substr(6));

    std::cout << "Diff View\n";
    bool differencesFound = false;

    for (size_t i = 0; i < std::min(blobs1.size(), blobs2.size()); ++i) {
        std::ifstream f1(".minigit/objects/" + blobs1[i]);
        std::ifstream f2(".minigit/objects/" + blobs2[i]);

        std::string l1, l2;
        int lineNum = 1;
        while (std::getline(f1, l1) && std::getline(f2, l2)) {
            if (l1 != l2) {
                std::cout << "Line " << lineNum << ":\n- " << l1 << "\n+ " << l2 << "\n";
                differencesFound = true;
            }
            ++lineNum;
        }

        // Catch extra lines
        while (std::getline(f1, l1)) {
            std::cout << "Line " << lineNum << ":\n- " << l1 << "\n+ \n";
            differencesFound = true;
            ++lineNum;
        }
        while (std::getline(f2, l2)) {
            std::cout << "Line " << lineNum << ":\n- \n+ " << l2 << "\n";
            differencesFound = true;
            ++lineNum;
        }
    }

    if (!differencesFound) {
        std::cout << "No differences found.\n";
    }
}