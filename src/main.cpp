#include "MiniGit.h"
#include "../commands/log.h"
#include "./commands/add.h"
#include "./commands/commit.h"

int main() {
    MiniGit repo;
    repo.init();
    addFileToStage("test.txt"); // test file to stage
    commit("Initial commit"); // commit staged file
    ShowLog();
    return 0;
}
// This is the main entry point for the MiniGit application.