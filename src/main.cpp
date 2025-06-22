#include "MiniGit.h"
#include "./commands/add.h"
int main() {
    MiniGit repo;
    repo.init();
    addFileToStage("test.txt"); // test file to stage
    return 0;
}
// This is the main entry point for the MiniGit application.
// It initializes a new MiniGit repository by creating the necessary directories and files.