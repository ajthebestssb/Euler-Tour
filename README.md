Euler Tour Technique (Subtree Flattening)

This repository contains a C++ implementation of the Euler Tour technique (specifically the Entry/Exit time method) and demonstrates its application in solving Subtree Sum Queries.

The Concept

The Euler Tour technique allows us to represent a Tree structure as a linear Array (or Vector). This "flattening" process is powerful because it converts complex tree operations into simpler array range operations.

How it works

We perform a Depth First Search (DFS) on the tree and maintain a global timer.

Time In (tin[u]): Recorded when we first enter a node.

Time Out (tout[u]): Recorded when we finish visiting all of a node's children and are about to leave it.

Property

For any node u, the subtree of u lies strictly within the continuous range [tin[u], tout[u]] in the flattened array.

Complexity

DFS Traversal: $O(N)$ - Preprocessing to calculate entry/exit times.

Point Update: $O(\log N)$ - Using a Fenwick Tree.

Subtree Query: $O(\log N)$ - Calculating sum over the flattened range.

Building and Running

Prerequisites

G++ Compiler

Steps

Clone the repo:

git clone <your-repo-url>


Compile the code:

g++ main.cpp -o euler_tour


Run the executable:

./euler_tour


File Structure

main.cpp: Contains the graph construction, DFS logic, Fenwick Tree implementation, and test cases.