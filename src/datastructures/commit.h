#pragma once
#include <string>
#include <vector>

struct Commit {
    std::string hash;
    std::string message;
    std::string timestamp;
    std::string parentHash;
    std::vector<std::string> blobHashes;
};