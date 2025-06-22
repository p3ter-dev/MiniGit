#include "./Hasher.h"
#include <sstream>
#include <iomanip>

std::string simpleHash(const std::string& content) {
    unsigned long hash = 5381;
    for (char c : content) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Convert to hex
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}