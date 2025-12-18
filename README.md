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
- Initially used CUnit for unit testing, later migrated to Unity for fully self-contained, portable test suites

## Usage
1. Clone the repository: `git clone https://github.com/Milad244/dsa-power`
2. Enter the project directory: `cd dsa-power`
3. Build the main program: `make`
4. Run the main program: `./build/main`
5. Build the tests: `make tests`
6. Run the tests: `./build/test_<name>`
7. Clean build artifacts: `make clean`

## Acknowledgments
- Some build setup, tooling ideas, and boilerplate tests were assisted by AI.