#ifndef BLOB_H
#define BLOB_H

#include <string>

class Blob {
public:
    // Constructor: takes in the file path, reads it and computes hash
    Blob(const std::string& filename);

    // Save content to blob file (.minigit/objects/<hash>)
    void writeToObjectStore() const;

    // Getter for hash (used in indexing, commits)
    std::string getHash() const;

    // Getter for file name (optional use)
    std::string getFilename() const;

private:
    std::string filename;
    std::string content;
    std::string hash;

    // Helper to load content and hash
    void readAndHashFile();
};

#endif
