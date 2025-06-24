# MiniGit: A Custom Version Control System ✨

---

## 🚀 Project Overview

MiniGit is a lightweight, local-only version control system implemented from scratch in C++. It simulates core Git functionalities, including repository initialization, staging and committing file changes, viewing commit history, branching, switching contexts (`checkout`), comparing versions (`diff`), and performing basic merges.

This project serves as a practical exploration into the core mechanics of modern version control, demonstrating fundamental Data Structures and Algorithms (DSA) principles applied in a real-world software engineering context.

---

## 👥 Prepared by:

1.  **Peter Kinfe** — ATE/7749/15
2.  **Abenezer Degife** — ATE/2172/15
3.  **Kirubel Yitagesu** — ATE/9761/15
4.  **Mintesnot Assefa** — ATE/1203/16
5.  **Biruk Mulugeta** — ATE/7635/15
6.  **Yohannis Million** — ATE/9533/16
7.  **Yordanos Tarekegn** — ATE/5260/14

---

## 📽️ Project Demo

Watch a short demonstration of MiniGit's functionalities in action:

* **Demo Video on Loom:** [https://www.loom.com/share/4b09a07e4803443dbf94c01504f30026?sid=e43fd34b-7743-4275-b949-71aa93a8f54d](https://www.loom.com/share/4b09a07e4803443dbf94c01504f30026?sid=e43fd34b-7743-4275-b949-71aa93a8f54d)

---

## ✨ Features Implemented

MiniGit currently supports the following command-line operations:

* ✅ **`minigit init`**: Initializes a new MiniGit repository in the current directory, creating the necessary `.minigit/` structure.
* ✅ **`minigit add <filename>`**: Stages a file for the next commit. Computes a hash of the file's content and stores it as a blob object.
* ✅ **`minigit commit -m "<message>"`**: Saves the current state of staged files as a new commit, creating a snapshot of the repository.
* ✅ **`minigit log`**: Displays the commit history starting from the current `HEAD` and traversing backward through parent commits.
* ✅ **`minigit branch <branch-name>`**: Creates a new branch pointing to the current commit.
* ✅ **`minigit checkout <branch-name>|<commit-hash>`**: Switches to a specified branch or detaches `HEAD` to a specific commit. Restores files from the target commit.
* ✅ **`minigit diff <commit1-hash> <commit2-hash>`**: Compares the content of files between two specified commits and displays the differences.
* ✅ **`minigit merge <target-branch>`**: Merges the specified `target-branch` into the current branch, performing a basic 3-way merge.

---

## 🛠️ How to Build / Compile

To compile and run MiniGit, you will need a C++ compiler (e.g., `g++` or `clang`).

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/p3ter-dev/MiniGit.git](https://github.com/p3ter-dev/MiniGit.git)
    cd MiniGit
    ```

2.  **Compile the source code:**
    Navigate to the root directory of the cloned repository and run your C++ compiler.
    *(Adjust compiler flags as necessary for your environment. `-std=c++17` for `std::filesystem` and `-lstdc++fs` for linking are common requirements.)*

    ```bash
    # For Linux/macOS
    g++ -o minigit src/*.cpp src/commands/*.cpp src/datastructures/*.cpp src/utils/*.cpp -std=c++17 -lstdc++fs

    # For Windows with MinGW/MSYS2 (output will be minigit.exe)
    # g++ -o minigit.exe src/*.cpp src/commands/*.cpp src/datastructures/*.cpp src/utils/*.cpp -std=c++17 -lstdc++fs
    ```
    *If you are using CMake, your build process would typically be:*
    ```bash
    # mkdir build && cd build
    # cmake ..
    # make # or `cmake --build .`
    ```

---

## 🚀 How to Use

Navigate to a directory where you want to initialize your MiniGit repository.

```bash
# 1. Initialize a new repository
./minigit init

# 2. Create some files
echo "Hello MiniGit!" > example.txt
echo "This is another file." > another.txt

# 3. Add files to the staging area
./minigit add example.txt
./minigit add another.txt

# 4. Commit the staged changes
./minigit commit -m "Initial commit: Added example.txt and another.txt"

# 5. Make changes and create a new commit
echo "Added a new line." >> example.txt
./minigit add example.txt
./minigit commit -m "Second commit: Updated example.txt"

# 6. View commit history
./minigit log

# 7. Create and switch to a new branch
./minigit branch feature-branch
./minigit checkout feature-branch

# 8. Make changes on the new branch
echo "Content for feature." > feature-file.txt
./minigit add feature-file.txt
./minigit commit -m "Feature commit: Added feature-file.txt"

# 9. Switch back to main and merge the feature branch
./minigit checkout main
./minigit merge feature-branch

# 10. View differences between two commits (replace with actual commit hashes from `minigit log`)
# ./minigit diff <commit-hash-1> <commit-hash-2>