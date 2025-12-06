# DSA Power

## Description
DSA Power is a collection of my own implementations of core data structures and algorithms in C.
It includes:

- **Data Structures:** VLA, Singly Linked List, Doubly Linked List, Stack, Queue, Binary Tree, Binary Search Tree
- **Algorithms:** Sorting (Selection, Bubble, Insertion, Merge, Quick), Searching (Linear, Binary)

This repository is designed for practicing and understanding fundamental concepts in data structures and algorithms.

## Status
Ongoing. 2025-11-13 to present.

## Resources Used
- C for implementing data structures and algorithms
- CUnit for unit testing
- AI assistance for help with the Makefile and managing dependencies

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
