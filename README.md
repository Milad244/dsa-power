# DSA Power

## Description
DSA Power is a collection of my own implementations of core data structures and algorithms in C.
I developed this project to practice and deeply understand fundamental concepts in data structures and algorithms.
I also added rigorous unit testing to gain experience creating DRY tests and to overcome my mental block with testing large programs.
Most importantly, this project is designed for first-year CS students who want a beginner-friendly and readable program containing all the data structures they will learn. If you are learning DSA, I highly recommend trying to implement the functions yourself and using my test cases to help verify your solutions.

This project covers:

- **Data Structures:**
  - VLA (Variable-Length Array)
  - Singly Linked List
  - Doubly Linked List
  - Stack
  - Queue
  - Binary Tree
  - Binary Search Tree

- **Algorithms:**
  - Sorting: Selection, Bubble, Insertion, Merge, Quick
  - Searching: Linear, Binary
  - Additional utility algorithms included with each data structure, such as node_distance and traversal functions

## Status
Ongoing. 2025-11-13 to present.

## Resources Used
- C for implementing data structures and algorithms
- CUnit for unit testing

## Usage
1. Clone the repository: `git clone https://github.com/Milad244/dsa-power`
2. Enter the project directory: `cd dsa-power`
3. Build the main program (no dependencies required): `make`
4. Run the main program: `./build/main`
5. Run tests (requires [CUnit](http://cunit.sourceforge.net/) installed):
   - macOS (Homebrew): `brew install cunit` then `make test`
   - Linux (Debian/Ubuntu): `sudo apt install libcunit1-dev` then `make test`
   - Windows: Install CUnit via MSYS2, Cygwin, or a compatible build, then run `make test EXTRA_CFLAGS="-IC:/path/to/CUnit/include" EXTRA_LDFLAGS="-LC:/path/to/CUnit/lib"`
6. Clean build artifacts: `make clean`

## Acknowledgments
- Some build setup and tooling ideas were assisted by AI.