# **Project Overview**
   
MiniGit is a lightweight, local-only version control system meticulously crafted from scratch in C++. This project serves as a foundational exploration into the core mechanics of modern version control, simulating essential Git functionalities such as repository initialization, staging changes, committing snapshots, viewing history, creating branches, switching contexts, calculating differences between commits, and performing basic merges.

It demonstrates a practical application of fundamental Data Structures and Algorithms (DSA) principles, including hashing for content-addressing, efficient file I/O, graph traversal for commit history, and basic conflict resolution, all orchestrated through a Command-Line Interface (CLI).




## **1. Data Structures Used**

MiniGit leverages a combination of in-memory C++ standard library containers and a robust file-system based persistence layer to manage version control data.

- **File System (Primary Persistence Layer)**:
    - The entire repository state is persistently stored within a hidden `.minigit/` directory. This design mirrors Git's object database.
    - `.minigit/objects/`: Stores immutable Blob objects. Each blob is a file named after its content hash.
    - `.minigit/commits/`: Stores immutable Commit objects. Each commit is a file named after its hash, containing metadata and pointers to file blobs and   parent commits.
    - `.minigit/refs/`: Stores branch and tag references as files. For instance, refs/main contains the hash of the latest commit on the main branch.
    - `.minigit/HEAD`: A file pointing to the current branch (ref: refs/main) or a specific commit hash (detached HEAD).
    - `.minigit/stage`: A simple text file serving as the staging area, listing the blob hashes of files prepared for the next commit.

- **Blob (`Blob` Class):**
    - `Blob.h`, `Blob.cpp`: Represents a file's content at a specific version.
    - **Attributes:** `std::string filename` (though currently used primarily for internal identification in Blob class, not consistently for file restoration by `checkout` which relies on hash.txt naming) and `std::string hash`.
    - **Functionality:** Stores actual file content in the `.minigit/objects/` directory, named by its hash.
    - **DSA Concepts:** Hashing (for content addressing), File I/O.

- **Commit Object (File-based representation)**:
    - Managed by `commit.cpp`, `FileIO.cpp`: Represents a snapshot of the repository.
    - Structure (within file): `commit: <hash>`, `timestamp: <date>`, `message: <msg>`, `parent: <parent_hash>`, and `blob: <blob_hash>` lines for each file.
    - DSA Concepts: Implicit Linked List / Directed Acyclic Graph (DAG) for commit history, formed by parent pointers.

- **Staging Area (via `minigit/stage`)**:
    - Managed by `add.cpp`, `commit.cpp`, `FileIO.cpp`: A simple flat-file index of staged file blob hashes.
    - Internal Representation (in code): `std::vector<std::string>` to hold the list of blob hashes read from `.minigit/stage`.
    - DSA Concepts: Dynamic Array/List for in-memory representation.

- **Branch References and HEAD (via `.minigit/refs/` and `.minigit/HEAD` files)**:
    - Managed by `minigit.cpp`, `commit.cpp`, `branch.cpp`, `checkout.cpp`, `FileIO.cpp`: Lightweight pointers to specific commit hashes.
    - Internal Representation: Simple text files.
    - DSA Concepts: Key-Value Store (conceptually, where branch names are keys and commit hashes are values).

- **Hashing (`Hasher.h`, `Hasher.cpp`)**:
    - Utilizes a custom `simpleHash` function to generate unique identifiers for file contents and commit data.
    - DSA Concepts: Hashing algorithm.

- **Utility Data Structures:**
    - `std::vector<std::string>`: Used extensively for collecting lists of blob hashes (e.g., in `readStagedFiles`).
    - `std::unordered_set<std::string>`: Used in `merge.cpp` for efficient lookup of commit ancestors during Lowest Common Ancestor (LCA) calculation.
    - `std::unordered_map<std::string, std::string>`: Used in `merge.cpp` to map filenames (represented by `hash + ".txt"`) to their blob hashes within a commit.   



## **2. Design Decisions**

- **File-Based Object Storage:** Adopting a Git-like object model where all versioned content and metadata are stored as individual files named by their hash within a `.minigit/` directory. This simplifies persistence and makes the repository's internal state transparent.

- **Content-Addressable Blobs:** Files are stored as "blobs" identified by the hash of their content. This ensures data integrity, enables deduplication of identical file contents, and forms the basis for detecting changes.

- **Immutable Objects:** Once created, `Blob` and `Commit` objects are never modified. Any change results in a new object, preserving history.

- **Simple Hashing Algorithm:** The use of `simpleHash` for generating unique IDs for blobs and commits simplifies the cryptographic complexity for this educational project while fulfilling the core requirement of unique identification.

- **Linear Commit History (Initial Focus):** While the DSA Project.pdf mentions DAGs, the primary parentHash field in commit files and the readParentHash function suggests a focus on linear commit history initially, with merge extending this to handle a basic form of branching history.

- **Clear Separation of Concerns (Modular Design):**
    - `src/commands/`: Houses the implementations for each CLI command (`add`, `commit`, `log`, `branch`, `checkout`, `diff`, `merge`), promoting modularity.
    - `src/datastructures/`: Contains classes or definitions for core Git objects like `Blob` (and conceptually `Commit` if it were a full class).
    - `src/utils/`: Provides reusable utility functions for common tasks like file I/O and hashing, reducing code duplication.

- **Direct File Manipulation for State:** Instead of complex in-memory databases, the system directly reads from and writes to files like `.minigit/stage`, `.minigit/HEAD`, and files under `.minigit/refs/` to manage the repository's current state.

- **Basic Diffing:** The `diff` command implements a line-by-line comparison of two blob contents, demonstrating the fundamental concept of content difference.

- **Lowest Common Ancestor (LCA) for Merge:** The `merge` command implements a simplified 3-way merge by finding the LCA, which is a correct approach for understanding merge bases in Git.  



## **3. Limitations and Future Improvements**
While MiniGit provides a solid foundation for understanding version control, several areas can be enhanced for robustness, completeness, and a more Git-like experience.

**Current Limitations**

- **Filename Tracking in Blobs/Commits:**
    - Blob objects internally store filename, but commit.cpp only stores blob hashes in the commit file (blob: <hash>).
    - checkout.cpp uses blobHash + ".txt" as the filename for restoration, making it impossible to restore original filenames or handle files without .txt extensions. This is a significant deviation from how Git tracks files by their path in the index and tree objects.
    - This also impacts diff.cpp and merge.cpp, which compare blobs without context of their original filenames, leading to potential issues with multiple files having the same content (same hash).

- **Simple Staging Area:** The .minigit/stage file is a flat list of blob hashes. A robust staging area (Git's "index") would store (mode, filename, blob_hash) tuples, allowing for tracking of renamed, deleted, or executable files, and more precise staging.

- **Basic Diffing Mechanism:**
    - diff.cpp compares two blob files directly and assumes a one-to-one correspondence by std::min(blobs1.size(), blobs2.size()) iterating. It doesn't use filenames to intelligently match files across commits.
    - It only shows changes in existing lines, not context lines, and handles added/deleted lines in a rudimentary way.

- **Limited Merge Conflict Handling:** The merge.cpp only detects basic "both modified" conflicts and simply prints a message, without creating merge conflict markers in files or providing tools for resolution.

- **No Deletion/Renaming Tracking:** The system doesn't explicitly track file deletions or renames. Deleted files would simply vanish from the next commit's blob list, and renamed files would appear as a deletion of the old file and an addition of a new one.

- **Hashing Algorithm:** simpleHash is a basic, non-cryptographic hash function. A real Git implementation uses SHA-1 (and newer SHA-256) for strong content integrity and collision resistance.

- **Branch HEAD Management:** While checkout handles ref: refs/branch and detached HEADs, readCurrentHead() in FileIO.cpp still only reads from refs/main, which might not be correct when HEAD is detached.

- **No Reset/Revert:** Commands for undoing changes or reverting commits are not implemented.

- **No Status Command:** There is no minigit status to show the state of the working directory, staged changes, and uncommitted changes.

- **No Tagging:** The ability to create immutable pointers (tags) to specific commits is missing.


**Future Improvements**

- **Implement Proper Index/Tree Objects:**
    - Overhaul the staging area (.minigit/stage) to be an "index" file that stores (mode, filename, blob_hash) entries, mapping specific file paths to their blob hashes.
    - Introduce "Tree" objects that represent directories. A commit would then point to a single root Tree object, which in turn points to other Trees (subdirectories) or Blobs (files). This would resolve the filename tracking limitation.

- **Advanced `checkout`:**
    - Modify `checkout` to read the correct filenames from the commit's tree/index data and restore them accurately.
    - Add ability to `checkout <filename>` to restore a specific file from the index or a commit.

- **Refined `diff` Command:**
    - Implement a proper diffing algorithm (e.g., Myers's algorithm) that can show contextual differences, added lines, deleted lines, and efficiently compare different file versions across commits using their filenames.
    - Enable `diff` to work between working directory, staging area, and commits.

- **Comprehensive `merge` with Conflict Markers:**
    - When conflicts occur, modify the conflicting files in the working directory with standard Git-style conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`).
    - Provide a way to mark conflicts as resolved and then commit the merge.

- **Implement `status` Command:** Show modified, new, deleted, staged, and untracked files.

- **Implement `reset` and `revert`:** Allow users to undo commits and modify history.

- **Support for Deletion and Renaming:** Explicitly track file deletions and renames in the staging area and commit objects.

- **Branch Management:** Add commands for listing branches (`minigit branch`), deleting branches, and pushing/pulling branches if remote operations are added.

- **Remote Operations:** Implement `minigit clone`, `minigit fetch`, `minigit push`, `minigit pull` to interact with remote repositories. This would involve networking (TCP/IP sockets or HTTP).

- **Error Handling and User Feedback:** Enhance error messages to be more informative and user-friendly.

- **Robust Hashing:** Integrate a standard cryptographic hash function like SHA-1 or SHA-256 for stronger data integrity.

- **Automated Testing:** Implement a comprehensive suite of unit tests and integration tests to ensure all commands and data structures function correctly.


