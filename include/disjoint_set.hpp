#pragma once
#include <vector>
#include <numeric>

/**
 * @brief Disjoint Set Union (DSU) / Union-Find with Path Compression and Union by Rank
 *
 * Time Complexity:
 *   - Find: O(alpha(N)) amortized nearly O(1)
 *   - Union: O(alpha(N)) amortized nearly O(1)
 *   - Connected: O(alpha(N))
 * Space Complexity: O(N)
 */
class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> size;
    int num_components;

public:
    explicit DisjointSet(int n) : parent(n), rank(n, 0), size(n, 1), num_components(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    // Find with full path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false; // Already in the same component (indicates a cycle in undirected graphs)
        }

        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
            size[root_y] += size[root_x];
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
            size[root_x] += size[root_y];
        } else {
            parent[root_y] = root_x;
            size[root_x] += size[root_y];
            rank[root_x]++;
        }

        num_components--;
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int component_size(int x) {
        return size[find(x)];
    }

    int count_components() const {
        return num_components;
    }
};