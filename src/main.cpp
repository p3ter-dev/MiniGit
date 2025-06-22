#include "MiniGit.h"
#include "./commands/log.h"
#include "./commands/add.h"
#include "./commands/commit.h"
#include "./datastructures/branch.h"
using command::showLog;

int main() {
    MiniGit repo;
    repo.init();
    addFileToStage("test.txt"); // test file to stage
    commit("Initial commit"); // commit staged file
    showLog(); // display commit log
    createBranch("feature-something"); // create a new branch
    return 0;
}
// This is the main entry point for the MiniGit application.