#include "./commands/init.h"
#include "./commands/add.h"
#include "./commands/commit.h"
#include "./commands/log.h"
#include "./commands/checkout.h"
#include "./commands/merge.h"
#include "./datastructures/branch.h"
#include "./commands/diff.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: minigit <command> [args]\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        initRepo(); // Initializes a new MiniGit repository in the current directory.
    } 
    else if (command == "add") {
        if (argc < 3) {
            std::cerr << "Usage: minigit add <filename>\n";
            return 1;
        }
        addFileToStage(argv[2]); // Adds a file to the staging area.
    } 
    else if (command == "commit") {
        if (argc < 3) {
            std::cerr << "Usage: minigit commit -m <message>\n";
            return 1;
        }
        commit(argv[2]); // Commits the staged files with a message.
    } 
    else if (command == "log") {
        command::showLog(); // Displays the commit history.
    }
    else if (command == "checkout") {
        if (argc < 3) {
            std::cerr << "Usage: minigit checkout <branch-name|commit-hash>\n";
            return 1;
        }
        checkout(argv[2]); // Checks out a branch or a specific commit.
    }
    else if (command == "branch") {
        if (argc < 3) {
            std::cerr << "Usage: minigit branch <branch-name>\n";
            return 1;
        }
        createBranch(argv[2]); // Creates a new branch pointing to the current commit.
    }
    else if (command == "merge") {
        if (argc < 3) {
            std::cerr << "Usage: minigit merge <branch-name>\n";
            return 1;
        }
        merge(argv[2]); // Merges the specified branch into the current branch.
    }
    else if (command == "diff") {
        if (argc < 4) {
            std::cerr << "Usage: minigit diff <commit1> <commit2>\n";
            return 1;
        }
        diff(argv[2], argv[3]); // Displays the differences between two commits identified by their hashes.
    }
    else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}