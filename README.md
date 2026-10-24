# ⚡ Data Structures & Algorithms Practice in C++

[![C++](https://img.shields.io/badge/Language-C%2B%2B17%2F20-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![Focus](https://img.shields.io/badge/Focus-Algorithms_%26_Complexity-blueviolet)](#)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A curated collection of modular, production-standard **Data Structures and Algorithms** implemented in modern C++ (C++17/20). Features include cache designs, graph pathfinding, prefix trees, and sliding-window patterns with time & space complexity annotations.

---

## 📊 Implemented Topics & Complexity

| Data Structure / Algorithm | Category | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **LRU Cache** (`lru_cache.hpp`) | Cache / Hash Table | $O(1)$ Get & Put | $O(C)$ Capacity |
| **Trie (Prefix Tree)** (`trie.hpp`) | Strings / Trees | $O(L)$ Insert & Query | $O(N \cdot L)$ |
| **Dijkstra's Algorithm** (`main.cpp`) | Graphs / Shortest Path | $O((V + E) \log V)$ | $O(V + E)$ |
| **Sliding Window Max Sum** (`main.cpp`) | Array / Two Pointers | $O(N)$ Linear Time | $O(1)$ Constant |

---

## 📂 Project Structure

```
dsa-practice/
├── include/
│   ├── lru_cache.hpp           # Templated O(1) Least Recently Used cache
│   └── trie.hpp                # Prefix tree with autocomplete support
├── main.cpp                    # Test harness and benchmark runner
├── .gitignore
└── README.md
```

---

## 🚀 How to Build and Run

### Using `g++` / Clang (Terminal or VS Code):
```bash
# Compile with C++17 standard
g++ -std=c++17 main.cpp -o dsa_runner

# Execute
./dsa_runner
```

### On Windows (MinGW / MSVC):
```cmd
g++ -std=c++17 main.cpp -o dsa_runner.exe
dsa_runner.exe
```

---

## 🎯 Key Design Highlights
- **Modern C++ Idioms**: RAII (`std::unique_ptr`), structured bindings (`auto [u, v]`), and templates.
- **Cache-Friendly Data Structures**: Minimized memory fragmentation using Standard Template Library (STL).
- **Unit Tested**: Fully integrated validation tests included in `main.cpp`.

---

## 👤 Author
- **Syed Aamish** — [GitHub Profile](https://github.com/syedaamish11)
