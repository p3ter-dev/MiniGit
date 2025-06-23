#include "./commands/init.h"
#include "./commands/log.h"
#include "./commands/add.h"
#include "./commands/commit.h"
#include "./datastructures/branch.h"
#include "./commands/checkout.h"
#include "./commands/merge.h"
#include "./commands/diff.h"
using command::showLog;

int main() {
    initRepo();
    // addFileToStage("test.txt"); // test file to stage
    // commit("Initial commit"); // commit staged file
    // showLog(); // display commit log
    // createBranch("feature-test"); // create a new branch
    // checkout("main"); // Testing basic checkout print
    // merge("feature-test"); // merge feature test into main
    // showLog(); // display commit log after merge
    // diff("b3f97fa", "b3f97fa"); // display differences between two commits
    return 0;
}
// This is the main entry point for the MiniGit application.