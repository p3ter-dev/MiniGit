#pragma once
#include <string>
#include <vector>

std::string readFileContent(const std::string& filePath);
std::vector<std::string> readStagedFiles();
std::string readCurrentHead();// Reads the current HEAD commit hash (from .minigit/refs/main)
std::string readParentHash(const std::string& commitHash); // Reads the parent commit hash from a commit file