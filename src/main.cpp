#include "MiniGit.h"
#include "./commands/log.h"
#include "./commands/add.h"
#include "./commands/commit.h"
#include "./datastructures/branch.h"
#include "./commands/checkout.h"
using command::showLog;

int main() {
    MiniGit repo;
    repo.init();
    addFileToStage("test.txt"); // test file to stage
    commit("Initial commit"); // commit staged file
    showLog(); // display commit log
    createBranch("feature-something"); // create a new branch
    checkout("test-branch"); // Testing basic checkout print
    return 0;
}
// This is the main entry point for the MiniGit application.