#include "minigit.h"
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = filesystem;

void MiniGit::init() {
    fs::path minigitPath = ".minigit";

    if(fs::exists(minigitPath)) {
        cout << "Repository already initialized.\n";
        return;
    }

    try {
        fs::create_directory(minigitPath);
        fs::create_directory(minigitPath / "objects");
        fs::create_directory(minigitPath / "commits");
        fs::create_directory(minigitPath / "refs");

        // creating HEAD file and set it to point to main branch
        ofstream headFile(minigitPath / "HEAD");
        headFile << "ref: ref/main";
        headFile.close();
        
        // creating initial main branch ref file
        ofstream masterRef(minigitPath / "refs/main");
        masterRef.close();
        cout << "Initialized empty MiniGit repository in .minigit/\n";
    } catch (const exception& e) {
        cerr << "Error initializing MiniGit: " << e.what() << "\n";
    }
}