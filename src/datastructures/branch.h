#ifndef BRANCH_H
#define BRANCH_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// Creates a new branch pointing to the current commit
void createBranch(const std::string &branchName);

#endif