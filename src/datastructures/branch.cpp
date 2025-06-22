#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// Create a new branch pointing to the current commit
void createBranch(const std::string &branchName)
{
    fs::path repo = fs::current_path() / ".minigit";
    fs::path branchPath = repo / "refs" / branchName;

    // Check if branch already exists
    if (fs::exists(branchPath))
    {
        std::cerr << "Branch '" << branchName << "' already exists.\n";
        return;
    }

    // Read current commit hash from HEAD
    std::ifstream headFile(repo / "HEAD");
    std::string refLine;
    std::getline(headFile, refLine);
    headFile.close();

    std::string currentRef = refLine.substr(5); // remove "ref: "
    std::ifstream currentBranchFile(repo / currentRef);
    std::string currentCommit;
    std::getline(currentBranchFile, currentCommit);
    currentBranchFile.close();

    // Create new branch file with current commit hash
    std::ofstream newBranch(branchPath);
    newBranch << currentCommit;
    newBranch.close();

    std::cout << "Branch '" << branchName << "' created at commit " << currentCommit << "\n";
}

// Switch HEAD to point to a different branch
void switchBranch(const std::string &branchName)
{
    fs::path repo = fs::current_path() / ".minigit";
    fs::path branchPath = repo / "refs" / branchName;

    // Check if branch exists
    if (!fs::exists(branchPath))
    {
        std::cerr << "Branch '" << branchName << "' does not exist.\n";
        return;
    }

    // Update HEAD to point to this branch
    std::ofstream headFile(repo / "HEAD", std::ios::trunc);
    headFile << "ref: refs/" << branchName << "\n";
    headFile.close();

    std::cout << "Switched to branch '" << branchName << "'\n";
}
