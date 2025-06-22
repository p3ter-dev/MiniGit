#pragma once
#include <string>
#include <vector>

std::string readFileContent(const std::string& filePath);
std::vector<std::string> readStagedFiles();
std::string readCurrentHead();// Reads the current HEAD commit hash (from .minigit/refs/main)