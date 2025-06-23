# **Project Overview**
   
MiniGit is a lightweight, local-only version control system meticulously crafted from scratch in C++. This project serves as a foundational exploration into the core mechanics of modern version control, simulating essential Git functionalities such as repository initialization, staging changes, committing snapshots, viewing history, creating branches, switching contexts, calculating differences between commits, and performing basic merges.

It demonstrates a practical application of fundamental Data Structures and Algorithms (DSA) principles, including hashing for content-addressing, efficient file I/O, graph traversal for commit history, and basic conflict resolution, all orchestrated through a Command-Line Interface (CLI).


1. ## **Data Structures Used**

MiniGit leverages a combination of in-memory C++ standard library containers and a robust file-system based persistence layer to manage version control data.

- File System (Primary Persistence Layer):
    - The entire repository state is persistently stored within a hidden `.minigit/` directory. This design mirrors Git's object database.
    - `.minigit/objects/`: Stores immutable Blob objects. Each blob is a file named after its content hash.
    - `.minigit/commits/`: Stores immutable Commit objects. Each commit is a file named after its hash, containing metadata and pointers to file blobs and   parent commits.
    - `.minigit/refs/`: Stores branch and tag references as files. For instance, refs/main contains the hash of the latest commit on the main branch.
    - `.minigit/HEAD`: A file pointing to the current branch (ref: refs/main) or a specific commit hash (detached HEAD).
    - `.minigit/stage`: A simple text file serving as the staging area, listing the blob hashes of files prepared for the next commit.

- Blob (Blob Class):
    - Blob.h, Blob.cpp: Represents a file's content at a specific version.
    - Attributes: std::string filename (though currently used primarily for internal identification in Blob class, not consistently for file restoration by checkout which relies on hash.txt naming) and std::string hash.
    - Functionality: Stores actual file content in the .minigit/objects/ directory, named by its hash.
    - DSA Concepts: Hashing (for content addressing), File I/O.

- Commit Object (File-based representation):
    - Managed by commit.cpp, FileIO.cpp: Represents a snapshot of the repository.
    - Structure (within file): commit: <hash>, timestamp: <date>, message: <msg>, parent: <parent_hash>, and blob: <blob_hash> lines for each file.
    - DSA Concepts: Implicit Linked List / Directed Acyclic Graph (DAG) for commit history, formed by parent pointers.

- Staging Area (via minigit/stage):
    - Managed by add.cpp, commit.cpp, FileIO.cpp: A simple flat-file index of staged file blob hashes.
    - Internal Representation (in code): std::vector<std::string> to hold the list of blob hashes read from .minigit/stage.
    - DSA Concepts: Dynamic Array/List for in-memory representation.

