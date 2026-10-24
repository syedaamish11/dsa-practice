#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

/**
 * @brief Prefix Tree (Trie) for String Operations & Autocomplete
 * Time Complexity:
 *   - Insertion: O(L) where L is string length
 *   - Search: O(L)
 *   - Prefix Search: O(L)
 */
class Trie {
private:
    struct TrieNode {
        bool is_end_of_word = false;
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    };

    std::unique_ptr<TrieNode> root;

    void collectWords(const TrieNode* node, const std::string& prefix, std::vector<std::string>& results) const {
        if (!node) return;
        if (node->is_end_of_word) {
            results.push_back(prefix);
        }
        for (const auto& [ch, child] : node->children) {
            collectWords(child.get(), prefix + ch, results);
        }
    }

public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& word) {
        TrieNode* current = root.get();
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_unique<TrieNode>();
            }
            current = current->children[ch].get();
        }
        current->is_end_of_word = true;
    }

    bool search(const std::string& word) const {
        const TrieNode* current = root.get();
        for (char ch : word) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current != nullptr && current->is_end_of_word;
    }

    bool startsWith(const std::string& prefix) const {
        const TrieNode* current = root.get();
        for (char ch : prefix) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current != nullptr;
    }

    std::vector<std::string> autocomplete(const std::string& prefix) const {
        std::vector<std::string> results;
        const TrieNode* current = root.get();
        for (char ch : prefix) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) {
                return results;
            }
            current = it->second.get();
        }
        collectWords(current, prefix, results);
        return results;
    }
};
