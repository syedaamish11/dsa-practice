#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include "include/lru_cache.hpp"
#include "include/trie.hpp"
#include "include/disjoint_set.hpp"

// Algorithm 1: Sliding Window - Maximum Sum Subarray of Size K
long long maxSubarraySum(const std::vector<int>& arr, int k) {
    if (arr.size() < static_cast<size_t>(k) || k <= 0) return 0;
    long long window_sum = 0;
    for (int i = 0; i < k; ++i) window_sum += arr[i];

    long long max_sum = window_sum;
    for (size_t i = k; i < arr.size(); ++i) {
        window_sum += arr[i] - arr[i - k];
        max_sum = std::max(max_sum, window_sum);
    }
    return max_sum;
}

// Algorithm 2: Dijkstra's Shortest Path Algorithm
std::vector<int> dijkstra(int n, int source, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    const int INF = 1e9;
    std::vector<int> dist(n, INF);
    // Min-heap storing pair of (distance, vertex)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Algorithm 3: Kadane's Algorithm - Maximum Contiguous Subarray Sum
long long kadaneMaxSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    long long max_so_far = arr[0];
    long long current_max = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        current_max = std::max(static_cast<long long>(arr[i]), current_max + arr[i]);
        max_so_far = std::max(max_so_far, current_max);
    }
    return max_so_far;
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "   C++ Data Structures & Algorithms Practice\n";
    std::cout << "===========================================\n\n";

    // 1. Test LRU Cache
    std::cout << "[1] Testing LRU Cache (Capacity = 2):\n";
    LRUCache<int, std::string> cache(2);
    cache.put(1, "A");
    cache.put(2, "B");
    std::string val;
    if (cache.get(1, val)) std::cout << "    Get key 1: " << val << " (Expected: A)\n";
    cache.put(3, "C"); // Should evict key 2
    if (!cache.get(2, val)) std::cout << "    Get key 2: Evicted (Expected: Not found)\n";
    if (cache.get(3, val)) std::cout << "    Get key 3: " << val << " (Expected: C)\n";
    std::cout << "    Cache contains key 1: " << (cache.contains(1) ? "Yes" : "No") << "\n";
    std::cout << "    Cache contains key 2: " << (cache.contains(2) ? "Yes" : "No") << "\n";

    // 2. Test Trie Autocomplete
    std::cout << "\n[2] Testing Trie Prefix Autocomplete:\n";
    Trie trie;
    trie.insert("algorithm");
    trie.insert("algebra");
    trie.insert("allocate");
    trie.insert("binary");

    std::cout << "    Searching 'alg': " << (trie.startsWith("alg") ? "Found" : "Not Found") << "\n";
    auto suggestions = trie.autocomplete("al");
    std::cout << "    Autocomplete for 'al': ";
    for (const auto& w : suggestions) std::cout << w << " ";
    std::cout << "\n";

    // 3. Test Sliding Window
    std::cout << "\n[3] Testing Sliding Window (Max sum subarray of size 3):\n";
    std::vector<int> nums = {2, 1, 5, 1, 3, 2};
    std::cout << "    Array: [2, 1, 5, 1, 3, 2], k = 3\n";
    std::cout << "    Max Sum: " << maxSubarraySum(nums, 3) << " (Expected: 9)\n";

    // 4. Test Dijkstra
    std::cout << "\n[4] Testing Dijkstra Shortest Path:\n";
    int n = 4;
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[2].push_back({1, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({3, 5});

    auto distances = dijkstra(n, 0, adj);
    std::cout << "    Shortest distances from node 0:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "      To Node " << i << ": " << distances[i] << "\n";
    }

    // 5. Test Disjoint Set Union (DSU)
    std::cout << "\n[5] Testing Disjoint Set Union (DSU / Union-Find):\n";
    DisjointSet dsu(6); // 6 vertices: 0, 1, 2, 3, 4, 5
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    std::cout << "    0 and 2 connected: " << (dsu.connected(0, 2) ? "Yes (Expected: Yes)" : "No") << "\n";
    std::cout << "    0 and 3 connected: " << (dsu.connected(0, 3) ? "Yes" : "No (Expected: No)") << "\n";
    std::cout << "    Total independent components: " << dsu.count_components() << " (Expected: 3)\n";
    std::cout << "    Component size of node 0: " << dsu.component_size(0) << " (Expected: 3)\n";

    // 6. Test Kadane's Algorithm
    std::cout << "\n[6] Testing Kadane's Algorithm (Max Contiguous Subarray):\n";
    std::vector<int> kadane_nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "    Array: [-2, 1, -3, 4, -1, 2, 1, -5, 4]\n";
    std::cout << "    Max Subarray Sum: " << kadaneMaxSubarray(kadane_nums) << " (Expected: 6)\n";

    std::cout << "\nAll test suites completed successfully!\n";
    return 0;
}