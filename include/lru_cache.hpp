#pragma once
#include <unordered_map>
#include <list>
#include <utility>
#include <stdexcept>

/**
 * @brief Least Recently Used (LRU) Cache
 * Time Complexity: O(1) for both get and put operations
 * Space Complexity: O(Capacity)
 */
template <typename KeyType, typename ValueType>
class LRUCache {
private:
    size_t capacity;
    // List stores pairs of (key, value) with most recently used at the front
    std::list<std::pair<KeyType, ValueType>> items;
    // Hash map stores iterator to the list node for O(1) access
    std::unordered_map<KeyType, typename std::list<std::pair<KeyType, ValueType>>::iterator> lookup;

public:
    explicit LRUCache(size_t cap) : capacity(cap) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than zero.");
        }
    }

    bool get(const KeyType& key, ValueType& out_value) {
        auto it = lookup.find(key);
        if (it == lookup.end()) {
            return false;
        }
        // Move accessed item to the front of the list
        items.splice(items.begin(), items, it->second);
        out_value = it->second->second;
        return true;
    }

    void put(const KeyType& key, const ValueType& value) {
        auto it = lookup.find(key);
        if (it != lookup.end()) {
            // Key already exists, update value and move to front
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }

        // Evict least recently used if at capacity
        if (items.size() >= capacity) {
            auto lru = items.back();
            lookup.erase(lru.first);
            items.pop_back();
        }

        // Insert new item at the front
        items.emplace_front(key, value);
        lookup[key] = items.begin();
    }

    bool contains(const KeyType& key) const {
        return lookup.find(key) != lookup.end();
    }

    size_t size() const {
        return items.size();
    }

    bool empty() const {
        return items.empty();
    }

    void clear() {
        items.clear();
        lookup.clear();
    }
};