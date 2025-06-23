#pragma once
#include <string>

void diff(const std::string& hash1, const std::string& hash2);
// Displays the differences between two commits identified by their hashes.
// If the hashes are the same, it will show that there are no differences.