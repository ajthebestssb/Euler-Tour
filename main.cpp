/**
 * Euler Tour Technique (Subtree Flattening)
 * -----------------------------------------
 * This program demonstrates how to linearize a tree using DFS entry and exit times.
 * This technique maps every subtree to a contiguous range in an array.
 *
 * Application demonstrated: Dynamic Subtree Sum Queries
 * - Update the value of a specific node.
 * - Query the sum of values in the subtree of a specific node.
 *
 * Time Complexity:
 * - Preprocessing (DFS): O(N)
 * - Update: O(log N)
 * - Query: O(log N)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum number of nodes
const int MAXN = 100005;

// Graph adjacency list
vector<int> adj[MAXN];

// Euler Tour arrays
int tin[MAXN];      // Time In: When DFS enters the node
int tout[MAXN];     // Time Out: When DFS leaves the node
int timer;          // Global timer
int flat_array[MAXN]; // Maps time -> initial node value (for building BIT)

// Binary Indexed Tree (Fenwick Tree) for range queries
long long bit[MAXN];
int n; // Number of nodes

// --- Euler Tour Logic ---
void dfs(int u, int p) {
    // Record entry time
    tin[u] = ++timer;
    
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    
    // Record exit time
    tout[u] = timer;
}

// --- Fenwick Tree Logic ---
void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += val;
}

long long query(int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

// Query range [l, r]
long long query_range(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    // 1. Setup Sample Tree
    // Structure:
    //       1
    //     /   \
    //    2     3
    //   / \
    //  4   5
    
    n = 5;
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(1);

    // Initial values for nodes 1 to 5
    vector<int> values = {0, 10, 20, 30, 40, 50}; // 0-indexed dummy, values start at index 1

    cout << "--- Euler Tour Algorithm Demo ---\n";

    // 2. Run Euler Tour (DFS)
    timer = 0;
    dfs(1, 0); // Start DFS from root (node 1)

    // Output Mapping
    cout << "Node Mapping (Time In | Time Out):\n";
    for(int i = 1; i <= n; i++) {
        cout << "Node " << i << ": [" << tin[i] << ", " << tout[i] << "]\n";
        // Initialize BIT with initial values at the position of their entry time
        update(tin[i], values[i]);
    }
    cout << "\n";

    // 3. Application: Subtree Queries
    // The subtree of Node U corresponds to the range [tin[U], tout[U]] in the linear array.
    
    // Query 1: Sum of subtree of Node 2 (Should include Node 2, 4, 5 -> 20 + 40 + 50 = 110)
    cout << "Querying Subtree Sum of Node 2...\n";
    cout << "Range: [" << tin[2] << ", " << tout[2] << "]\n";
    long long sum = query_range(tin[2], tout[2]);
    cout << "Result: " << sum << " (Expected: 110)\n\n";

    // Query 2: Update Node 4 value from 40 to 100
    cout << "Updating Node 4 value to 100...\n";
    int diff = 100 - values[4];
    update(tin[4], diff);
    values[4] = 100;

    // Query 3: Query Subtree of Node 2 again (Should be 20 + 100 + 50 = 170)
    cout << "Querying Subtree Sum of Node 2 (after update)...\n";
    sum = query_range(tin[2], tout[2]);
    cout << "Result: " << sum << " (Expected: 170)\n";

    return 0;
}