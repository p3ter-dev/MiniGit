#include "./commands/init.h"
#include "./commands/add.h"
#include "./commands/commit.h"
#include "./commands/log.h"
#include "./commands/checkout.h"
#include "./commands/merge.h"
#include "./commands/diff.h"
#include "./datastructures/branch.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: minigit <command> [options]\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        initRepo();
    }
    else if (command == "add") {
        if (argc < 3) {
            std::cout << "Usage: minigit add <filename>\n";
            return 1;
        }
        addFileToStage(argv[2]);
    }
    else if (command == "commit") {
        if (argc >= 4 && std::string(argv[2]) == "-m") {
            std::string message = argv[3];
            commit(message);
        } else {
            std::cout << "Usage: minigit commit -m \"commit message\"\n";
        }
    }
    else if (command == "log") {
        command::showLog();
    }
    else if (command == "branch") {
        if (argc < 3) {
            std::cout << "Usage: minigit branch <branch-name>\n";
            return 1;
        }
        createBranch(argv[2]);
    }
    else if (command == "checkout") {
        if (argc < 3) {
            std::cout << "Usage: minigit checkout <branch-name|commit-hash>\n";
            return 1;
        }
        checkout(argv[2]);
    }
    else if (command == "merge") {
        if (argc < 3) {
            std::cout << "Usage: minigit merge <branch-name>\n";
            return 1;
        }
        merge(argv[2]);
    }
    else if (command == "diff") {
        if (argc < 4) {
            std::cout << "Usage: minigit diff <commit1> <commit2>\n";
            return 1;
        }
        diff(argv[2], argv[3]);
    }
    else {
        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}